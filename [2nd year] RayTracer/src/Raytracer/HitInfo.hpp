/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** HitInfo
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Raytracer {
    struct HitInfo {
        Math::Point3D point;
        Math::Vector3D normal;
        double distance;
        double u = 0.0;
        double v = 0.0;
    };
}
