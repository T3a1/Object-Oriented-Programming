/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Scene
*/

#include "Scene.hpp"
#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <fstream>
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "LimitedCylinder.hpp"
#include "LimitedCone.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Color.hpp"

namespace Raytracer {

    PPMImage Scene::readPPM(const std::string& filename) const {
        std::ifstream file(filename, std::ios::binary);
        std::string magic;
        int width, height, maxval;
        
        file >> magic >> width >> height >> maxval;
        file.get();
        
        PPMImage img;
        img.width = width;
        img.height = height;
        img.data.resize(width * height * 3);
        file.read((char*)img.data.data(), width * height * 3);
        return img;
    }

volatile std::sig_atomic_t g_cancel_requested = 0;

void handleSignal([[maybe_unused]] int sig) {
    g_cancel_requested = 1;
}

void Scene::addShape(std::shared_ptr<IShape> shape) {
    _shapes.push_back(shape);
}

void Scene::addLight(std::shared_ptr<ILight> light) {
    _lights.push_back(light);
}

void Scene::setCamera(const Camera& camera) {
    _camera = camera;
}

const std::vector<std::shared_ptr<IShape>>& Scene::getShapes() const {
    return _shapes;
}

const std::vector<std::shared_ptr<ILight>>& Scene::getLights() const {
    return _lights;
}

const Camera& Scene::getCamera() const {
    return _camera;
}

bool Scene::isInShadow(const Math::Point3D& point, const Math::Vector3D& direction, double maxDistance) const {
    Ray shadow_ray(point, direction);
    
    for (const auto& shape : _shapes) {
        HitInfo hit;
        if (shape->hits(shadow_ray, hit) && hit.distance > 1e-6) {
            if (maxDistance > 0 && hit.distance >= maxDistance)
                continue;
            return true;
        }
    }
    return false;
}

ShadowInfo Scene::getShadowInfo(const Math::Point3D& point, const Math::Vector3D& direction, double maxDistance) const {
    Ray shadow_ray(point, direction);
    std::map<double, const IShape*> orderedHits;

    for (const auto& shape : _shapes) {
        HitInfo hit;
        if (shape->hits(shadow_ray, hit) && hit.distance > 1e-6) {
            if (maxDistance > 0 && hit.distance >= maxDistance)
                continue;

            double orderedDistance = hit.distance;
            int collision_count = 0;
            while (orderedHits.find(orderedDistance) != orderedHits.end() && collision_count < 50) {
                orderedDistance += std::numeric_limits<double>::epsilon() * (1 + collision_count);
                collision_count++;
            }
            if (collision_count < 50)
                orderedHits.insert({orderedDistance, shape.get()});
        }
    }

    ShadowInfo result;
    for (const auto& [distance, shape] : orderedHits) {
        (void)distance;
        auto [r, g, b, a] = shape->getColor().getColor();

        result.factor *= (1.0 - a);
        if (a >= 1.0) {
            result.transmission = Math::Vector3D(0.0, 0.0, 0.0);
            return result;
        }

        Math::Vector3D filter(
            (1.0 - a) + a * r,
            (1.0 - a) + a * g,
            (1.0 - a) + a * b
        );
        result.transmission.x *= filter.x;
        result.transmission.y *= filter.y;
        result.transmission.z *= filter.z;
    }
    return result;
}

void Scene::buildBVH() {
    if (_shapes.empty())
        return;

    std::vector<std::shared_ptr<IShape>> shapes(_shapes.begin(), _shapes.end());
    _bvh = std::make_shared<BVHNode>();
    _bvh->build(shapes, 0, shapes.size());
}

bool Scene::castRay(const Ray& ray, HitInfo& hitInfo, std::shared_ptr<IShape>& hitShape,
    std::multimap<double, ShapeHitInfo>& orderedShapes) const
{
    if (_bvh) {
        HitInfo bvhHit;
        if (_bvh->hits(ray, bvhHit)) {
            hitInfo = bvhHit;
            return true;
        }
        return false;
    }

    double closest_distance = std::numeric_limits<double>::infinity();
    hitShape = nullptr;
    
    for (const auto& shape : _shapes) {
        HitInfo tempHitInfo;
        if (shape->hits(ray, tempHitInfo)) {
            orderedShapes.insert({tempHitInfo.distance, {shape, tempHitInfo}});
            
            if (tempHitInfo.distance < closest_distance) {
                closest_distance = tempHitInfo.distance;
                hitShape = shape;
                hitInfo = tempHitInfo;
            }
        }
    }
    return hitShape != nullptr;
}

Math::Vector3D Scene::calculateBlendColor(std::multimap<double, ShapeHitInfo>& orderedShapes,
    const Raytracer::Color& bg_color) const
{
    if (orderedShapes.empty())
        return bg_color;

    Math::Vector3D blendedColor(bg_color);

    for (auto it = orderedShapes.rbegin(); it != orderedShapes.rend(); ++it) {
        const auto& shapeHitInfo = it->second;
        std::shared_ptr<IShape> shape = shapeHitInfo.shape;
        const HitInfo& cachedHitInfo = shapeHitInfo.hitInfo;
        
        Raytracer::Color shapeColor = shape->getColor();
        auto [baseR, baseG, baseB, a] = shapeColor.getColor();

        Math::Vector3D litShapeColor(baseR, baseG, baseB);
        litShapeColor = Math::Vector3D(0, 0, 0);
        for (const auto& light : _lights)
            litShapeColor += light->calculateColor(shapeColor, cachedHitInfo, *this);
        litShapeColor.x = std::min(1.0, litShapeColor.x);
        litShapeColor.y = std::min(1.0, litShapeColor.y);
        litShapeColor.z = std::min(1.0, litShapeColor.z);

        blendedColor = Math::Vector3D(
            litShapeColor.x * a + blendedColor.x * (1.0 - a),
            litShapeColor.y * a + blendedColor.y * (1.0 - a),
            litShapeColor.z * a + blendedColor.z * (1.0 - a)
        );
    }
    return blendedColor;
}

Math::Vector3D Scene::calculatePixelColor(const Ray& ray, const Raytracer::Color& bg_color) const {
    HitInfo hitInfo;
    std::shared_ptr<IShape> hitShape = nullptr;
    std::multimap<double, ShapeHitInfo> orderedHitShapes;

    if (!castRay(ray, hitInfo, hitShape, orderedHitShapes))
        return bg_color;

    Raytracer::Color shapeColor = hitShape->getColor();
    auto [r, g, b, a] = shapeColor.getColor();
    Math::Vector3D pixel_color(r, g, b);
    
    std::string filename = hitShape->getFilename();
    if (!filename.empty()) {
        PPMImage ppm_img = readPPM(filename);
        if (ppm_img.width > 0 && ppm_img.height > 0) {
            double scale_factor = 1.0;
            int ppm_x = ((int)(hitInfo.u * scale_factor * ppm_img.width)) % ppm_img.width;
            int ppm_y = ((int)(hitInfo.v * scale_factor * ppm_img.height)) % ppm_img.height;
            
            if (ppm_x < 0)
                ppm_x += ppm_img.width;
            if (ppm_y < 0)
                ppm_y += ppm_img.height;
            
            int idx = (ppm_y * ppm_img.width + ppm_x) * 3;
            pixel_color.x = ppm_img.data[idx] / 255.0;
            pixel_color.y = ppm_img.data[idx + 1] / 255.0;
            pixel_color.z = ppm_img.data[idx + 2] / 255.0;
        }
    }

    Raytracer::Color finalColor(pixel_color.x, pixel_color.y, pixel_color.z, a);
    Math::Vector3D final_color(0, 0, 0);
    for (const auto& light : _lights)
        final_color += light->calculateColor(finalColor, hitInfo, *this);

    final_color.x = std::min(1.0, final_color.x);
    final_color.y = std::min(1.0, final_color.y);
    final_color.z = std::min(1.0, final_color.z);

    double alpha = a;
    Math::Vector3D bgVec(0, 0, 0);
    
    orderedHitShapes.erase(orderedHitShapes.begin());

    Raytracer::Color backgroundColor = calculateBlendColor(orderedHitShapes, bg_color);
    std::tuple<double, double, double, double> bgRGBA = backgroundColor.getColor();
    bgVec.x = std::get<0>(bgRGBA);
    bgVec.y = std::get<1>(bgRGBA);
    bgVec.z = std::get<2>(bgRGBA);

    Math::Vector3D blended(
        alpha * final_color.x + (1.0 - alpha) * bgVec.x,
        alpha * final_color.y + (1.0 - alpha) * bgVec.y,
        alpha * final_color.z + (1.0 - alpha) * bgVec.z
    );

    blended.x = std::min(1.0, blended.x);
    blended.y = std::min(1.0, blended.y);
    blended.z = std::min(1.0, blended.z);

    return blended;
}

void Scene::applyAntialiasing(int samples)
{
    if (samples <= 1)
        return;

    int width = _width;
    int height = _height;
    std::vector<Math::Vector3D> newBuffer;
    newBuffer.reserve(width * height);

    int gridSize = static_cast<int>(std::floor(std::sqrt((double)samples)));
    if (gridSize <= 0)
        gridSize = 1;
    int totalSamplesPerPixel = gridSize * gridSize;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (g_cancel_requested) {
                newBuffer.push_back(Math::Vector3D(0, 0, 0));
                continue;
            }

            Math::Vector3D colorAccumulator(0, 0, 0);
            for (int j = 0; j < gridSize; ++j) {
                for (int i = 0; i < gridSize; ++i) {
                    double subPixelOffsetX = ((double)i + 0.5) / (double)gridSize - 0.5;
                    double subPixelOffsetY = ((double)j + 0.5) / (double)gridSize - 0.5;
                    double normalizedScreenU = ((double)x + 0.5 + subPixelOffsetX) / (double)width;
                    double normalizedScreenV = ((double)(height - 1 - y) + 0.5 + subPixelOffsetY) / (double)height;
                    Ray cameraRay = _camera.ray(normalizedScreenU, normalizedScreenV);
                    colorAccumulator += calculatePixelColor(cameraRay, _background_color);
                }
            }

            colorAccumulator.x /= (double)totalSamplesPerPixel;
            colorAccumulator.y /= (double)totalSamplesPerPixel;
            colorAccumulator.z /= (double)totalSamplesPerPixel;
            newBuffer.push_back(colorAccumulator);
        }
    }

    _pixelBuffer = std::move(newBuffer);
}

void Scene::renderScene(int width, int height, const Raytracer::Color& bg_color, int antialiasing) {
    _pixelBuffer.clear();
    _pixelBuffer.reserve(width * height);

    std::signal(SIGINT, handleSignal);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double u = (double)x / (double)width;
            double v = (double)(height - 1 - y) / (double)height;

            if (!g_cancel_requested) {
                Ray ray = _camera.ray(u, v);
                Math::Vector3D pixel_color = calculatePixelColor(ray, bg_color);
                _pixelBuffer.push_back(pixel_color);
            } else
                _pixelBuffer.push_back(Math::Vector3D(0, 0, 0));
        }
    }

    applyAntialiasing(antialiasing);

    saveBufferToFile("output.ppm");
    std::cout << "File generation done !\n";
}

void Scene::renderScenePreview(int width, int height, const Raytracer::Color& bg_color) {
    _pixelBuffer.clear();
    _pixelBuffer.reserve(width * height);

    std::signal(SIGINT, handleSignal);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double u = (double)x / (double)width;
            double v = (double)(height - 1 - y) / (double)height;

            if (!g_cancel_requested) {
                Ray ray = _camera.ray(u, v);
                HitInfo hitInfo;
                std::shared_ptr<IShape> hitShape = nullptr;
                std::multimap<double, ShapeHitInfo> orderedShapes;

                Math::Vector3D pixelColor = castRay(ray, hitInfo, hitShape, orderedShapes)
                    ? hitShape->getColor() : bg_color;
                _pixelBuffer.push_back(pixelColor);
            } else
                _pixelBuffer.push_back(Math::Vector3D(0, 0, 0));
        }
    }
    saveBufferToFile("preview.ppm");
    std::cout << "Preview saved to preview.ppm\n";
}

void Scene::saveBufferToFile(const std::string& filename) const {
    std::FILE* file = std::fopen(filename.c_str(), "w");
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << " for writing\n";
        return;
    }

    std::fprintf(file, "P3\n%d %d\n255\n", _width, _height);
    size_t pixel_count = 0;
    for (const auto& pixel : _pixelBuffer) {
        // Clamp to [0.0, 1.0] and convert to [0, 255]
        int r = static_cast<int>(std::round(std::max(0.0, std::min(1.0, pixel.x)) * 255.0));
        int g = static_cast<int>(std::round(std::max(0.0, std::min(1.0, pixel.y)) * 255.0));
        int b = static_cast<int>(std::round(std::max(0.0, std::min(1.0, pixel.z)) * 255.0));
        
        std::fprintf(file, "%d %d %d ", r, g, b);
        
        pixel_count++;
        if (pixel_count % _width == 0)
            std::fprintf(file, "\n");
    }
    std::fclose(file);
    std::cout << "Saved to " << filename << std::endl;
}

}