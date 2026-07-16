/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Point
*/

#pragma once
#include "Vector3D.hpp"

namespace Math {
    class Point3D {
        public:
            double x;
            double y;
            double z;

            Point3D() = default;
            Point3D(double x, double y, double z);
            ~Point3D() = default;

            Point3D operator+(const Vector3D& vector) const;
            Point3D& operator+=(const Vector3D& vector);
            Point3D operator-(const Vector3D& vector) const;
            Point3D& operator-=(const Vector3D& vector);
            Point3D operator*(const Vector3D& vector) const;
            Point3D& operator*=(const Vector3D& vector);
            Point3D operator/(const Vector3D& vector) const;
            Point3D& operator/=(const Vector3D& vector);
    };
}
