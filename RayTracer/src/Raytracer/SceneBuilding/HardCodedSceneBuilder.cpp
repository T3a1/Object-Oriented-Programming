/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** HardCodedSceneBuilder
*/

#include "HardCodedSceneBuilder.hpp"
#include "Shapes/GroupShape.hpp"
#include "Shapes/LimitedCylinder.hpp"
#include "Shapes/LimitedCone.hpp"
#include "Color.hpp"

namespace Raytracer {

HardCodedSceneBuilder::HardCodedSceneBuilder(ShapeFactory& shapeFactory, LightFactory& lightFactory)
    :_shapeFactory(shapeFactory), _lightFactory(lightFactory)
{
}

void HardCodedSceneBuilder::buildCamera(Scene& scene) {
    Math::Point3D camOrigin(0.0, 1.5, 0.05);
    Math::Point3D viewportOrigin(-4.0, 0.5, 8.0);
    Math::Vector3D bottomSide(8.0, 0.0, 0.0);
    Math::Vector3D leftSide(0.0, 8.0, 0.0);

    scene.setCamera(Camera(camOrigin, viewportOrigin, bottomSide, leftSide));
    scene.setResolution(800, 800);
    scene.setBackgroundColor(Raytracer::Color(1.0, 1.0, 1.0, 1.0));
}


void HardCodedSceneBuilder::buildPrimitives(Scene& scene) {
    auto ground = _shapeFactory.createPlane(
        Math::Point3D(0.0, 0.0, 0.0), Math::Vector3D(0.0, 0.1, 0.0)
    );
    ground->setColor(Raytracer::Color(0.45, 0.27, 0.12, 1.0));

    scene.addShape(ground);
}

void HardCodedSceneBuilder::buildLights(Scene& scene) {
    auto ambientLight = _lightFactory.createAmbientLight(
        0.5, Math::Vector3D(1.0, 1.0, 1.0)
    );
    scene.addLight(std::shared_ptr<ILight>(std::move(ambientLight)));

    auto directionalLight = _lightFactory.createDirectionalLight(
        Math::Vector3D(2.0, 3.0, 2.0), 0.85, Math::Vector3D(1.0, 1.0, 1.0)
    );
    scene.addLight(std::shared_ptr<ILight>(std::move(directionalLight)));

    auto pointLight = _lightFactory.createPointLight(
        Math::Point3D(0.7, 1.5, 4.0), 2.0, Math::Vector3D(1.0, 1.0, 0.0)
    );
    scene.addLight(std::shared_ptr<ILight>(std::move(pointLight)));
}

void HardCodedSceneBuilder::buildGroups(Scene& scene) {
    auto tree = std::make_shared<GroupShape>("tree");
    tree->setReferencePoint(Math::Point3D(0.0, 6.0, 14.0));
    auto trunk = std::make_shared<LimitedCylinder>(
        Math::Point3D(0.0, 2.0, 14.0), Math::Vector3D(0.0, 1.0, 0.0), 0.3, 5.0
    );
    trunk->setColor(Raytracer::Color(0.45, 0.27, 0.12, 1.0));
    tree->addShape(trunk);
    
    auto foliage = std::make_shared<LimitedCone>(
        Math::Point3D(0.0, 5.0, 14.0), Math::Vector3D(0.0, -1.0, 0.0), 30.0, 4.0
    );
    foliage->setColor(Raytracer::Color(0.0, 0.5, 0.0, 0.8));
    tree->addShape(foliage);

    auto foliage2 = std::make_shared<LimitedCone>(
        Math::Point3D(0.0, 6.5, 14.0), Math::Vector3D(0.0, -1.0, 0.0), 28.0, 3.0
    );
    foliage2->setColor(Raytracer::Color(0.1, 0.7, 0.0, 0.8));
    tree->addShape(foliage2);

    auto foliage3 = std::make_shared<LimitedCone>(
        Math::Point3D(0.0, 8.0, 14.0), Math::Vector3D(0.0, -1.0, 0.0), 25.0, 2.5
    );
    foliage3->setColor(Raytracer::Color(0.2, 0.9, 0.0, 0.8));
    tree->addShape(foliage3);

    scene.addShape(tree);
}

}
