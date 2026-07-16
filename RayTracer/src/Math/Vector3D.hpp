/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Vector3D
*/

#pragma once
#include <cmath>
#include <string>

namespace Math {
    class Vector3D {
        public:
            double x;
            double y;
            double z;
            std::string file_name;


            Vector3D() = default;
            Vector3D(double x, double y, double z);
            ~Vector3D() = default;

            double length() const;
            double dot(const Vector3D& other) const;
            Vector3D cross(const Vector3D& other) const;
            Vector3D normalize() const;

            Vector3D operator+(const Vector3D& other) const;
            Vector3D& operator+=(const Vector3D& other);
            Vector3D operator-(const Vector3D& other) const;
            Vector3D& operator-=(const Vector3D& other);
            Vector3D operator*(const Vector3D& other) const;
            Vector3D& operator*=(const Vector3D& other);
            Vector3D operator/(const Vector3D& other) const;
            Vector3D& operator/=(const Vector3D& other);

            Vector3D operator*(double scalar) const;
            Vector3D& operator*=(double scalar);
            Vector3D operator/(double scalar) const;
            Vector3D& operator/=(double scalar);
    };
}
