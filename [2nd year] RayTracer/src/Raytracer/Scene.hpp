/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Scene
*/

#pragma once
#include <vector>
#include <memory>
#include <limits>
#include <map>
#include "IShape.hpp"
#include "ILight.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "HitInfo.hpp"
#include "FileWatcher.hpp"
#include <csignal>
#include "BVHNode.hpp"

namespace Raytracer {

    struct PPMImage {
        std::vector<unsigned char> data;
        int width, height;
    };

    struct ShadowInfo {
        double factor = 1.0;
        Math::Vector3D transmission{1.0, 1.0, 1.0};
    };

    struct ShapeHitInfo {
        std::shared_ptr<IShape> shape;
        HitInfo hitInfo;
    };

    class Scene {
        public:
            Scene() = default;
            ~Scene() = default;

            void addShape(std::shared_ptr<IShape> shape);
            void addLight(std::shared_ptr<ILight> light);
            void setCamera(const Camera& camera);
            void setResolution(int width, int height) { _width = width; _height = height; }
            void setBackgroundColor(const Raytracer::Color& color) { _background_color = color; }

            const std::vector<std::shared_ptr<IShape>>& getShapes() const;
            const std::vector<std::shared_ptr<ILight>>& getLights() const;
            const Camera& getCamera() const;
            int getWidth() const { return _width; };
            int getHeight() const { return _height; };
            Raytracer::Color getBackgroundColor() const { return _background_color; };

            bool isInShadow(const Math::Point3D& point, const Math::Vector3D& direction,
                double maxDistance = 0.0) const;
            ShadowInfo getShadowInfo(const Math::Point3D& point, const Math::Vector3D& direction,
                double maxDistance = 0.0) const;
            bool castRay(const Ray& ray, HitInfo& hitInfo, std::shared_ptr<IShape>& hitShape,
                std::multimap<double, ShapeHitInfo>& orderedShapes) const;
            Math::Vector3D calculatePixelColor(const Ray& ray, const Raytracer::Color& bg_color) const;
            Math::Vector3D calculateBlendColor(std::multimap<double, ShapeHitInfo>& orderedShapes,
                const Raytracer::Color& bg_color) const;
            void renderScene(int width, int height, const Raytracer::Color& bg_color, int antialiasing = 1);
            void renderScenePreview(int width, int height, const Raytracer::Color& bg_color);
            void saveBufferToFile(const std::string& filename) const;
            PPMImage readPPM(const std::string& filename) const;   
            void buildBVH();
            void applyAntialiasing(int samples);

            private:
            std::vector<std::shared_ptr<IShape>> _shapes;
            std::vector<std::shared_ptr<ILight>> _lights;
            Camera _camera;
            int _width;
            int _height;
            Raytracer::Color _background_color;
            std::vector<Math::Vector3D> _pixelBuffer;
            std::shared_ptr<BVHNode> _bvh = nullptr;
    };
}
