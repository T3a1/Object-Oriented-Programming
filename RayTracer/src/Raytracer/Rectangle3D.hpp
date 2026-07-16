/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Rectangle3D
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    class Rectangle3D {
        public:
            Rectangle3D();
            Rectangle3D(const Math::Point3D& origin, const Math::Vector3D& bottom_side, const Math::Vector3D& left_side);
            ~Rectangle3D() = default;

            Math::Point3D pointAt(double x, double y) const;

            Math::Point3D _origin;
            Math::Vector3D _bottom_side;
            Math::Vector3D _left_side;
    };
}
