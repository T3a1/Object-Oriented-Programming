/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-27
** File description:
** ShapeFactory implementation
*/

#include "ShapeFactory.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "LimitedCylinder.hpp"
#include "LimitedCone.hpp"
#include "Triangle.hpp"
#include "ObjShape.hpp"
#include <iostream>
#include <unordered_map>
#include <functional>

namespace Raytracer {

    std::shared_ptr<AShape> ShapeFactory::createShape(const std::string& type) const
    {
        const auto it = _creators.find(type);
        if (it != _creators.end())
            return it->second();

        std::cerr << "Error: Unknown shape type '" << type << "'" << std::endl;
        return nullptr;
    }

    std::shared_ptr<AShape> ShapeFactory::createSphere(const Math::Point3D& center, double radius) const {
        return std::make_shared<Sphere>(center, radius);
    }

    std::shared_ptr<AShape> ShapeFactory::createPlane(const Math::Point3D& point, const Math::Vector3D& normal) const {
        return std::make_shared<Plane>(point, normal);
    }

    std::shared_ptr<AShape> ShapeFactory::createCylinder(const Math::Point3D& center, 
        const Math::Vector3D& axis, double radius) const {
        return std::make_shared<Cylinder>(center, axis, radius);
    }

    std::shared_ptr<AShape> ShapeFactory::createCone(const Math::Point3D& center, 
        const Math::Vector3D& axis, double radius) const {
        return std::make_shared<Cone>(center, axis, radius);
    }

    std::shared_ptr<AShape> ShapeFactory::createLimitedCylinder(const Math::Point3D& center, 
        const Math::Vector3D& axis, double radius, double height) const {
        return std::make_shared<LimitedCylinder>(center, axis, radius, height);
    }

    std::shared_ptr<AShape> ShapeFactory::createLimitedCone(const Math::Point3D& center, 
        const Math::Vector3D& axis, double radius, double height) const {
        return std::make_shared<LimitedCone>(center, axis, radius, height);
    }

    std::shared_ptr<AShape> ShapeFactory::createTriangle(
        const Math::Point3D& a, const Math::Point3D& b, const Math::Point3D& c) const {
        return std::make_shared<Triangle>(a, b, c);
    }

    std::shared_ptr<AShape> ShapeFactory::createObj(const std::string& filePath) {
        return std::make_shared<ObjShape>(filePath);
    }

    std::shared_ptr<AShape> ShapeFactory::createObjWithMtl(const std::string& filePath, const std::string& mtlPath) {
        return std::make_shared<ObjShape>(filePath, mtlPath);
    }
    void ShapeFactory::registerShapeCreator(
        const std::string& type, 
        std::function<std::shared_ptr<AShape>()> creator
    ) {
        _creators[type] = creator;
    }

    std::vector<std::string> ShapeFactory::getAvailableShapes() const {
        std::vector<std::string> result;
        for (const auto& pair : _creators) {
            result.push_back(pair.first);
        }
        return result;
    }
}
