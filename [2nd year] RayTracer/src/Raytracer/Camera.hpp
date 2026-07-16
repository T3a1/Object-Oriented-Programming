/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Camera
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Rectangle3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class Camera {
        public:
            Camera() = default;
            Camera(const Math::Point3D& origin, const Math::Point3D& screen_origin,
                const Math::Vector3D& bottom_side, const Math::Vector3D& left_side);
            ~Camera() = default;

            Ray ray(double x, double y) const;

            Math::Point3D _origin;
            Rectangle3D _screen;
    };
}
