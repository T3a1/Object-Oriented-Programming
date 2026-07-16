/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** LibConfigSceneBuilder
*/

#include "LibConfigSceneBuilder.hpp"
#include "ShapeFactory.hpp"
#include "LightFactory.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <cmath>
#include "Color.hpp"

namespace Raytracer {

LibConfigSceneBuilder::LibConfigSceneBuilder(
    const std::string& configFilePath,
    Raytracer::ShapeFactory& shapeFactory,
    Raytracer::LightFactory& lightFactory
)
    : _shapeFactory(shapeFactory), _lightFactory(lightFactory)
{
    try {
        _cfg.readFile(configFilePath.c_str());
    } catch (libconfig::FileIOException& e) {
        std::cerr << "Could not open file: " << e.what() << std::endl;
    } catch (libconfig::ParseException& e) {
        std::cerr << "Parse error at line " << e.getLine()
            << ": " << e.getError() << std::endl;
    }
}

void LibConfigSceneBuilder::buildCamera(Scene& scene) {
    try {
        libconfig::Setting& camera = _cfg.lookup("camera");
        libconfig::Setting& resolution = camera["resolution"];
        libconfig::Setting& camOrigin = camera["cam_origin"];
        libconfig::Setting& viewportOrigin = camera["viewport_origin"];
        libconfig::Setting& bottomSide = camera["bottom_side"];
        libconfig::Setting& leftSide = camera["left_side"];

        double fov = camera.exists("fov") ? (double)camera["fov"] : 60.0;
        int width = resolution["width"];
        int height = resolution["height"];

        Math::Point3D camOriginPoint(camOrigin["x"], camOrigin["y"], camOrigin["z"]);
        Math::Point3D viewportOriginPoint(viewportOrigin["x"], viewportOrigin["y"], viewportOrigin["z"]);
        Math::Vector3D bottomSideVector(bottomSide["x"], bottomSide["y"], 0);
        Math::Vector3D leftSideVector(leftSide["x"], leftSide["y"], 0);
        Math::Point3D viewportCenter = viewportOriginPoint
            + (bottomSideVector * 0.5)
            + (leftSideVector * 0.5);

        double viewportDistance = std::abs(viewportOriginPoint.z - camOriginPoint.z);
        if (viewportDistance == 0.0)
            viewportDistance = 1.0;

        double aspectRatio = static_cast<double>(width) / static_cast<double>(height);
        double verticalFov = fov * M_PI / 180.0;
        double viewportHeight = 2.0 * viewportDistance * std::tan(verticalFov / 2.0);
        double viewportWidth = viewportHeight * aspectRatio;

        double bottomLength = bottomSideVector.length();
        double leftLength = leftSideVector.length();
        if (bottomLength != 0.0)
            bottomSideVector = bottomSideVector / bottomLength * viewportWidth;
        if (leftLength != 0.0)
            leftSideVector = leftSideVector / leftLength * viewportHeight;
        Math::Point3D centeredViewportOrigin = viewportCenter
            - (bottomSideVector * 0.5)
            - (leftSideVector * 0.5);

        Raytracer::Color backgroundColorVector(1.0, 1.0, 1.0, 1.0);
        if (camera.exists("background_color")) {
            libconfig::Setting& backgroundColor = camera["background_color"];
            if (backgroundColor.exists("r") && backgroundColor.exists("g") && backgroundColor.exists("b")) {
                double r = backgroundColor["r"];
                double g = backgroundColor["g"];
                double b = backgroundColor["b"];
                double alpha = backgroundColor.exists("a") ? (double)backgroundColor["a"] : 1.0;
                backgroundColorVector = Raytracer::Color(r, g, b, alpha);
            }
        }

        scene.setCamera(Camera(camOriginPoint, centeredViewportOrigin, bottomSideVector, leftSideVector));
        scene.setResolution(width, height);
        scene.setBackgroundColor(backgroundColorVector);
    } catch (libconfig::SettingNotFoundException& e) {
        std::cerr << "Camera settings not found in config: " << e.what() << std::endl;
    }

}

void LibConfigSceneBuilder::buildPrimitives(Scene& scene) {
    try {
        libconfig::Setting& primitives = _cfg.lookup("primitives");
        buildPrimitivesWithContainer(primitives, nullptr, scene);
    } catch (libconfig::SettingNotFoundException& e) {
        std::cerr << "No primitives found in config: " << e.what() << std::endl;
    }
}

void LibConfigSceneBuilder::buildPrimitivesWithContainer(libconfig::Setting& primitives, std::shared_ptr<GroupShape> group, Scene& scene) {
    const std::map<std::string, std::function<void(libconfig::Setting&)>> loaders = {
        {"sphere", [this, group, &scene](libconfig::Setting& prim) { loadSphere(prim, group, scene); }},
        {"plane", [this, group, &scene](libconfig::Setting& prim) { loadPlane(prim, group, scene); }},
        {"cylinder", [this, group, &scene](libconfig::Setting& prim) { loadCylinder(prim, group, scene); }},
        {"cone", [this, group, &scene](libconfig::Setting& prim) { loadCone(prim, group, scene); }},
        {"limitedCylinder", [this, group, &scene](libconfig::Setting& prim) { loadLimitedCylinder(prim, group, scene); }},
        {"limitedCone", [this, group, &scene](libconfig::Setting& prim) { loadLimitedCone(prim, group, scene); }},
        {"triangle", [this, group, &scene](libconfig::Setting& prim) { loadTriangle(prim, group, scene); }},
        {"obj", [this, group, &scene](libconfig::Setting& prim) { loadObj(prim, group, scene); }},
    };

    for (int i = 0; i < primitives.getLength(); i++) {
        libconfig::Setting& prim = primitives[i];
        std::string type = prim["type"];
        auto it = loaders.find(type);
        if (it != loaders.end())
            it->second(prim);
        else
            std::cerr << "Unknown primitive type: " << type << std::endl;
    }
}

void LibConfigSceneBuilder::buildGroups(Scene& scene) {
    try {
        libconfig::Setting& groups = _cfg.lookup("groups");
        for (int i = 0; i < groups.getLength(); i++) {
            loadGroupShapes(groups[i], scene);
        }
    } catch (libconfig::SettingNotFoundException& e) {
        std::cerr << "No groups found in config: " << e.what() << std::endl;
    }
}

void LibConfigSceneBuilder::buildLights(Scene& scene) {
    loadAmbientLight(scene);
    loadDirectionalLights(scene);
    loadPointLights(scene);
}

void LibConfigSceneBuilder::loadGroupShapes(libconfig::Setting& prim, Scene& scene)
{
    std::string name(prim["name"]);
    libconfig::Setting& shapes = prim["shapes"];
    auto groupshape = std::make_shared<GroupShape>(name);

    buildPrimitivesWithContainer(shapes, groupshape, scene);
    scene.addShape(groupshape);
}

void LibConfigSceneBuilder::loadSphere(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& origin = settings["origin"];
    Math::Point3D center(origin["x"], origin["y"], origin["z"]);
    double radius = settings["radius"];

    auto sphere = _shapeFactory.createSphere(center, radius);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    sphere->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            sphere->setFilename(filename);
    }
    if (group)
        group->addShape(sphere);
    else
        scene.addShape(sphere);
}

void LibConfigSceneBuilder::loadPlane(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& origin = settings["origin"];
    libconfig::Setting& direction = settings["direction"];
    Math::Point3D center(origin["x"], origin["y"], origin["z"]);
    Math::Vector3D normal(direction["x"], direction["y"], direction["z"]);

    auto plane = _shapeFactory.createPlane(center, normal);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    plane->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            plane->setFilename(filename);
    }
    if (group)
        group->addShape(plane);
    else
        scene.addShape(plane);
}

void LibConfigSceneBuilder::loadCylinder(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& origin = settings["origin"];
    libconfig::Setting& direction = settings["direction"];
    Math::Point3D center(origin["x"], origin["y"], origin["z"]);
    Math::Vector3D axis(direction["x"], direction["y"], direction["z"]);
    double radius = settings["radius"];

    auto cylinder = _shapeFactory.createCylinder(center, axis, radius);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    cylinder->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            cylinder->setFilename(filename);
    }
    if (group)
        group->addShape(cylinder);
    else
        scene.addShape(cylinder);
}

void LibConfigSceneBuilder::loadCone(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& origin = settings["origin"];
    libconfig::Setting& direction = settings["direction"];
    Math::Point3D center(origin["x"], origin["y"], origin["z"]);
    Math::Vector3D axis(direction["x"], direction["y"], direction["z"]);
    double radius = settings["radius"];

    auto cone = _shapeFactory.createCone(center, axis, radius);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    cone->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            cone->setFilename(filename);
    }
    if (group)
        group->addShape(cone);
    else
        scene.addShape(cone);
}

void LibConfigSceneBuilder::loadLimitedCylinder(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& origin = settings["origin"];
    libconfig::Setting& direction = settings["direction"];
    Math::Point3D center(origin["x"], origin["y"], origin["z"]);
    Math::Vector3D axis(direction["x"], direction["y"], direction["z"]);
    double radius = settings["radius"];
    double height = settings["height"];

    auto cylinder = _shapeFactory.createLimitedCylinder(center, axis, radius, height);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    cylinder->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            cylinder->setFilename(filename);
    }
    if (group)
        group->addShape(cylinder);
    else
        scene.addShape(cylinder);
}

void LibConfigSceneBuilder::loadLimitedCone(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& origin = settings["origin"];
    libconfig::Setting& direction = settings["direction"];
    Math::Point3D center(origin["x"], origin["y"], origin["z"]);
    Math::Vector3D axis(direction["x"], direction["y"], direction["z"]);
    double radius = settings["radius"];
    double height = settings["height"];

    auto cone = _shapeFactory.createLimitedCone(center, axis, radius, height);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    cone->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            cone->setFilename(filename);
    }
    if (group)
        group->addShape(cone);
    else
        scene.addShape(cone);
}

void LibConfigSceneBuilder::loadTriangle(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    libconfig::Setting& pointA = settings["a"];
    libconfig::Setting& pointB = settings["b"];
    libconfig::Setting& pointC = settings["c"];

    Math::Point3D a(pointA["x"], pointA["y"], pointA["z"]);
    Math::Point3D b(pointB["x"], pointB["y"], pointB["z"]);
    Math::Point3D c(pointC["x"], pointC["y"], pointC["z"]);

    auto triangle = _shapeFactory.createTriangle(a, b, c);
    libconfig::Setting& color = prim["color"];
    double alpha = 1.0;
    if (color.exists("a"))
        alpha = (double)color["a"];
    triangle->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            triangle->setFilename(filename);
    }
    if (group)
        group->addShape(triangle);
    else
        scene.addShape(triangle);
}

void LibConfigSceneBuilder::loadObj(libconfig::Setting& prim, std::shared_ptr<GroupShape> group, Scene& scene)
{
    libconfig::Setting& settings = prim["settings"];
    std::string filePath = settings["file"];

    std::shared_ptr<AShape> obj;
    if (settings.exists("mtl")) {
        std::string mtlPath = settings["mtl"];
        obj = _shapeFactory.createObjWithMtl(filePath, mtlPath);
    } else {
        obj = _shapeFactory.createObj(filePath);
        libconfig::Setting& color = prim["color"];
        double alpha = color.exists("a") ? (double)color["a"] : 1.0;
        obj->setColor(Raytracer::Color(color["r"], color["g"], color["b"], alpha));
    }

    if (prim.exists("texture_filename")) {
        std::string filename = prim["texture_filename"];
        if (!filename.empty())
            obj->setFilename(filename);
    }
    if (settings.exists("reference_point")) {
        libconfig::Setting& rp = settings["reference_point"];
        obj->setReferencePoint(Math::Point3D(rp["x"], rp["y"], rp["z"]));
    }
    if (settings.exists("scale")) {
        double factor = settings["scale"];
        obj->scale(factor);
    }
    if (settings.exists("rotateX")) {
        double degrees = settings["rotateX"];
        obj->rotateX(degrees);
    }
    if (settings.exists("rotateY")) {
        double degrees = settings["rotateY"];
        obj->rotateY(degrees);
    }
    if (settings.exists("rotateZ")) {
        double degrees = settings["rotateZ"];
        obj->rotateZ(degrees);
    }
    if (settings.exists("translate")) {
        libconfig::Setting& t = settings["translate"];
        obj->translate(Math::Vector3D(t["x"], t["y"], t["z"]));
    }
    if (auto objGroup = std::dynamic_pointer_cast<GroupShape>(obj))
        objGroup->buildBVH();

    if (group)
        group->addShape(std::dynamic_pointer_cast<AShape>(obj));
    else
        scene.addShape(obj);
}

void LibConfigSceneBuilder::loadAmbientLight(Scene& scene) {
    try {
        libconfig::Setting& ambient = _cfg.lookup("lights.ambient");
        double intensity = ambient["intensity"];
        Raytracer::Color color(ambient["color"]["r"], ambient["color"]["g"], ambient["color"]["b"], 1.0);
        auto light = _lightFactory.createAmbientLight(intensity, static_cast<Math::Vector3D>(color));
        scene.addLight(std::shared_ptr<ILight>(std::move(light)));
    } catch (libconfig::SettingNotFoundException&) {
        std::cerr << "No ambient light found in config." << std::endl;
    }
}

void LibConfigSceneBuilder::loadDirectionalLights(Scene& scene) {
    try {
        libconfig::Setting& directional = _cfg.lookup("lights.directional");
        for (int i = 0; i < directional.getLength(); i++) {
            libconfig::Setting& light = directional[i];
            Math::Vector3D direction(light["direction"]["x"], light["direction"]["y"], light["direction"]["z"]);
            Raytracer::Color color(light["color"]["r"], light["color"]["g"], light["color"]["b"], 1.0);
            double intensity = light["intensity"];
            auto newLight = _lightFactory.createDirectionalLight(direction, intensity, static_cast<Math::Vector3D>(color));
            scene.addLight(std::shared_ptr<ILight>(std::move(newLight)));
        }
    } catch (libconfig::SettingNotFoundException&) {
        std::cerr << "No directional lights found in config." << std::endl;
    }
}

void LibConfigSceneBuilder::loadPointLights(Scene& scene) {
    try {
        libconfig::Setting& point = _cfg.lookup("lights.point");
        for (int i = 0; i < point.getLength(); i++) {
            libconfig::Setting& light = point[i];
            Math::Point3D position(light["position"]["x"], light["position"]["y"], light["position"]["z"]);
            Raytracer::Color color(light["color"]["r"], light["color"]["g"], light["color"]["b"], 1.0);
            double intensity = light["intensity"];
            auto newLight = _lightFactory.createPointLight(position, intensity, static_cast<Math::Vector3D>(color));
            scene.addLight(std::shared_ptr<ILight>(std::move(newLight)));
        }
    } catch (libconfig::SettingNotFoundException&) {
        std::cerr << "No point lights found in config." << std::endl;
    }
}

}