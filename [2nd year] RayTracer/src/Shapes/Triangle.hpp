/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Triangle
*/

#pragma once
#include "AShape.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace Raytracer {
    class Triangle : public AShape {
        public:
            Triangle() = default;
            Triangle(const Math::Point3D &a, const Math::Point3D &b, const Math::Point3D &c);
            ~Triangle() = default;

            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            void translate(const Math::Vector3D& offset) override;
            void rotateX(double degrees) override;
            void rotateY(double degrees) override;
            void rotateZ(double degrees) override;
            void scale(double factor) override;

            Math::Point3D getReferencePoint() const override { return _center; }
            void setReferencePoint(const Math::Point3D& point) override;
            AABB getBoundingBox() const override;

            Math::Point3D _a;
            Math::Point3D _b;
            Math::Point3D _c;
            Math::Point3D _center;
            Math::Vector3D _normal;

        private:
            void computeNormal();
    };
}
