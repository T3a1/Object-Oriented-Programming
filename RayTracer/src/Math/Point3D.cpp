/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Point3D
*/

#include "Point3D.hpp"

namespace Math {

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z)
{
}

Point3D Point3D::operator+(const Vector3D &vector) const {
    return Point3D(x + vector.x, y + vector.y, z + vector.z);
}

Point3D &Point3D::operator+=(const Vector3D &vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Point3D Point3D::operator-(const Vector3D &vector) const {
    return Point3D(x - vector.x, y - vector.y, z - vector.z);
}

Point3D &Point3D::operator-=(const Vector3D &vector) {
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

Point3D Point3D::operator*(const Vector3D &vector) const {
    return Point3D(x * vector.x, y * vector.y, z * vector.z);
}

Point3D &Point3D::operator*=(const Vector3D &vector) {
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    return *this;
}

Point3D Point3D::operator/(const Vector3D &vector) const {
    return Point3D(x / vector.x, y / vector.y, z / vector.z);
}

Point3D &Point3D::operator/=(const Vector3D &vector) {
    x /= vector.x;
    y /= vector.y;
    z /= vector.z;
    return *this;
}

}
