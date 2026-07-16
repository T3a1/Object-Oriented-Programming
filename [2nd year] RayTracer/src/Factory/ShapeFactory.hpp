/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-27
** File description:
** ShapeFactory - Factory Pattern for creating shapes
*/

#pragma once
#include "AShape.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "LimitedCylinder.hpp"
#include "LimitedCone.hpp"
#include "Triangle.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

namespace Raytracer {
    class ShapeFactory {
        public:
            ShapeFactory() = default;
            ~ShapeFactory() = default;

            std::shared_ptr<AShape> createShape(const std::string& type) const;
            std::shared_ptr<AShape> createSphere(const Math::Point3D& center, double radius) const;
            std::shared_ptr<AShape> createPlane(const Math::Point3D& point, const Math::Vector3D& normal) const;
            std::shared_ptr<AShape> createCylinder(const Math::Point3D& center, 
                const Math::Vector3D& axis, double radius) const;
            std::shared_ptr<AShape> createCone(const Math::Point3D& center, 
                const Math::Vector3D& axis, double radius) const;
            std::shared_ptr<AShape> createLimitedCylinder(const Math::Point3D& center, 
                const Math::Vector3D& axis, double radius, double height) const;
            std::shared_ptr<AShape> createLimitedCone(const Math::Point3D& center, 
                const Math::Vector3D& axis, double radius, double height) const;
            std::shared_ptr<AShape> createTriangle(const Math::Point3D& a, const Math::Point3D& b, const Math::Point3D& c) const;
            std::shared_ptr<AShape> createObj(const std::string& filePath);
            std::shared_ptr<AShape> createObjWithMtl(const std::string& filePath, const std::string& mtlPath);

            void registerShapeCreator(
                const std::string& type, 
                std::function<std::shared_ptr<AShape>()> creator
            );
            std::vector<std::string> getAvailableShapes() const;
            void clearCreators() {
                _creators.clear();
            }

        private:
            std::unordered_map<std::string, std::function<std::shared_ptr<AShape>()>> _creators = {
                {"sphere", []() { return std::make_shared<Sphere>(); }},
                {"plane", []() { return std::make_shared<Plane>(); }},
                {"cylinder", []() { return std::make_shared<Cylinder>(); }},
                {"cone", []() { return std::make_shared<Cone>(); }},
                {"limited_cylinder", []() { return std::make_shared<LimitedCylinder>(); }},
                {"limited_cone", []() { return std::make_shared<LimitedCone>(); }},
                {"triangle", []() { return std::make_shared<Triangle>(); }},
            };
    };
}