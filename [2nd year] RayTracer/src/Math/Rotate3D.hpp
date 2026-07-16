/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Rotate3D
*/

# pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"

namespace Math {
    Point3D rotatePointX(const Point3D& point, const Point3D& center, double degrees);
    Point3D rotatePointY(const Point3D& point, const Point3D& center, double degrees);
    Point3D rotatePointZ(const Point3D& point, const Point3D& center, double degrees);

    Vector3D rotateVectorX(const Vector3D& vector, double degrees);
    Vector3D rotateVectorY(const Vector3D& vector, double degrees);
    Vector3D rotateVectorZ(const Vector3D& vector, double degrees);
}
