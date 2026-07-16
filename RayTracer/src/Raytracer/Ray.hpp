/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Ray
*/

#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace Raytracer {
    class Ray {
        public:
            Ray() = default;
            Ray(const Math::Point3D& origin, const Math::Vector3D& direction);
            ~Ray() = default;

            Math::Point3D _origin;
            Math::Vector3D _direction;
    };
}
