/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** AABB
*/

#include "AABB.hpp"
#include <algorithm>
#include <cmath>

namespace Raytracer {

AABB::AABB(const Math::Point3D& min, const Math::Point3D& max) : _min(min), _max(max)
{
}

void AABB::expand(const AABB& other) {
    _min.x = std::min(_min.x, other._min.x);
    _min.y = std::min(_min.y, other._min.y);
    _min.z = std::min(_min.z, other._min.z);
    _max.x = std::max(_max.x, other._max.x);
    _max.y = std::max(_max.y, other._max.y);
    _max.z = std::max(_max.z, other._max.z);
}

void AABB::expand(const Math::Point3D& point) {
    _min.x = std::min(_min.x, point.x);
    _min.y = std::min(_min.y, point.y);
    _min.z = std::min(_min.z, point.z);
    _max.x = std::max(_max.x, point.x);
    _max.y = std::max(_max.y, point.y);
    _max.z = std::max(_max.z, point.z);
}

bool AABB::hits(const Ray& ray, double rayDistanceMin, double rayDistanceMax) const {
    auto getAxisPoint = [&](int axis, const Math::Point3D& point) {
        if (axis == 0)
            return point.x;
        if (axis == 1)
            return point.y;
        return point.z;
    };
    auto getAxisVector = [&](int axis, const Math::Vector3D& vec) {
        if (axis == 0)
            return vec.x;
        if (axis == 1)
            return vec.y;
        return vec.z;
    };

    for (int axis = 0; axis < 3; axis++) {
        double rayOriginOnAxis = getAxisPoint(axis, ray._origin);
        double rayDirectionOnAxis = getAxisVector(axis, ray._direction);
        double nearLimit = getAxisPoint(axis, _min);
        double farLimit = getAxisPoint(axis, _max);
        double inverseDirection = 1.0 / rayDirectionOnAxis;
        double nearEntryDistance = (nearLimit - rayOriginOnAxis) * inverseDirection;
        double farExitDistance = (farLimit  - rayOriginOnAxis) * inverseDirection;

        if (inverseDirection < 0.0)
            std::swap(nearEntryDistance, farExitDistance);
        rayDistanceMin = std::max(rayDistanceMin, nearEntryDistance);
        rayDistanceMax = std::min(rayDistanceMax, farExitDistance);
        if (rayDistanceMax <= rayDistanceMin)
            return false;
    }
    return true;
}

Math::Point3D AABB::getCenter() const {
    return Math::Point3D(
        (_min.x + _max.x) / 2.0,
        (_min.y + _max.y) / 2.0,
        (_min.z + _max.z) / 2.0
    );
}

int AABB::getLongestAxis() const {
    double dx = _max.x - _min.x;
    double dy = _max.y - _min.y;
    double dz = _max.z - _min.z;
    if (dx >= dy && dx >= dz)
        return 0;
    if (dy >= dz)
        return 1;
    return 2;
}

}
