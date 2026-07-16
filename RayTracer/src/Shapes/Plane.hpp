/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Plane
*/

#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "AShape.hpp"

namespace Raytracer {
    class Plane : public AShape {
        public:
            Plane() = default;
            Plane(const Math::Point3D& point, const Math::Vector3D& normal);
            ~Plane() = default;

            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            void translate(const Math::Vector3D& offset) override;
            void rotateX(double degrees) override;
            void rotateY(double degrees) override;
            void rotateZ(double degrees) override;
            void scale([[maybe_unused]]double factor) override {};

            Math::Point3D getReferencePoint() const override { return _point; }
            void setReferencePoint(const Math::Point3D& point) override { _point = point; }

            Math::Point3D _point;
            Math::Vector3D _normal;
    };
}
