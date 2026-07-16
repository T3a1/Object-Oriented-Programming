/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Sphere
*/

#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "AShape.hpp"

namespace Raytracer {
    class Sphere : public AShape {
        public:
            Sphere() = default;
            Sphere(const Math::Point3D& center, double radius);
            ~Sphere() = default;

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
            double _radius;
    };
}
