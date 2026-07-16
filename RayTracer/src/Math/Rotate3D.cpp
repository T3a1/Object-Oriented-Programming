/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Rotate3D
*/

#include "Rotate3D.hpp"

namespace Math {

Math::Point3D rotatePointX(const Math::Point3D& point, const Math::Point3D& pivot, double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);
    Math::Vector3D relative(point.x - pivot.x, point.y - pivot.y, point.z - pivot.z);

    return Math::Point3D(
        pivot.x + relative.x,
        pivot.y + relative.y * cosA - relative.z * sinA,
        pivot.z + relative.y * sinA + relative.z * cosA
    );
}

Math::Point3D rotatePointY(const Math::Point3D& point, const Math::Point3D& pivot, double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);
    Math::Vector3D relative(point.x - pivot.x, point.y - pivot.y, point.z - pivot.z);

    return Math::Point3D(
        pivot.x + relative.x * cosA + relative.z * sinA,
        pivot.y + relative.y,
        pivot.z - relative.x * sinA + relative.z * cosA
    );
}

Math::Point3D rotatePointZ(const Math::Point3D& point, const Math::Point3D& pivot, double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);
    Math::Vector3D relative(point.x - pivot.x, point.y - pivot.y, point.z - pivot.z);

    return Math::Point3D(
        pivot.x + relative.x * cosA - relative.y * sinA,
        pivot.y + relative.x * sinA + relative.y * cosA,
        pivot.z + relative.z
    );
}

Math::Vector3D rotateVectorX(const Math::Vector3D& vector, double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    return Math::Vector3D(
        vector.x,
        vector.y * cosA - vector.z * sinA,
        vector.y * sinA + vector.z * cosA
    );
}

Math::Vector3D rotateVectorY(const Math::Vector3D& vector, double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    return Math::Vector3D(
        vector.x * cosA + vector.z * sinA,
        vector.y,
        -vector.x * sinA + vector.z * cosA
    );
}

Math::Vector3D rotateVectorZ(const Math::Vector3D& vector, double degrees)
{
    double radians = degrees * M_PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    return Math::Vector3D(
        vector.x * cosA - vector.y * sinA,
        vector.x * sinA + vector.y * cosA,
        vector.z
    );
}

}