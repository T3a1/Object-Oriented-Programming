/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Cylinder
*/

#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "AShape.hpp"

namespace Raytracer {
    class Cylinder : public AShape {
        public:
            Cylinder() = default;
            Cylinder(const Math::Point3D& baseCenter, const Math::Vector3D& axis,
                double radius);
            ~Cylinder() = default;

            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            void translate(const Math::Vector3D& offset) override;
            void rotateX(double degrees) override;
            void rotateY(double degrees) override;
            void rotateZ(double degrees) override;
            void scale(double factor) override;

            Math::Point3D getReferencePoint() const override { return _baseCenter; }
            void setReferencePoint(const Math::Point3D& point) override { _baseCenter = point; }

            Math::Point3D _baseCenter;
            Math::Vector3D _axis;
            double _radius;
    };
}
