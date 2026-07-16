/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Cone
*/

#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "AShape.hpp"

namespace Raytracer {
    class Cone : public AShape {
        public:
            Cone() = default;
            Cone(const Math::Point3D& apex, const Math::Vector3D& axis, double angle);
            ~Cone() = default;

            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            void translate(const Math::Vector3D& offset) override;
            void rotateX(double degrees) override;
            void rotateY(double degrees) override;
            void rotateZ(double degrees) override;
            void scale([[maybe_unused]]double factor) override {};

            Math::Point3D getReferencePoint() const override { return _apex; }
            void setReferencePoint(const Math::Point3D& point) override { _apex = point; }

            Math::Point3D _apex;
            Math::Vector3D _axis;
            double _angle;
    };
}
