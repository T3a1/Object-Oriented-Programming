/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Limited Cylinder
*/

#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "AShape.hpp"

namespace Raytracer {
    class LimitedCylinder : public AShape {
        public:
            LimitedCylinder() = default;
            LimitedCylinder(const Math::Point3D& center, const Math::Vector3D& axis,
                double radius, double height);
            ~LimitedCylinder() = default;

            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            void translate(const Math::Vector3D& offset) override;
            void rotateX(double degrees) override;
            void rotateY(double degrees) override;
            void rotateZ(double degrees) override;
            void scale(double factor) override;

            Math::Point3D getReferencePoint() const override { return _center; }
            void setReferencePoint(const Math::Point3D& point) override { _center = point; }
            AABB getBoundingBox() const override;

            Math::Point3D _center;
            Math::Vector3D _axis;
            double _radius;
            double _height;
    };
}
