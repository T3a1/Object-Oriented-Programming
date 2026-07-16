/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Limited Cone
*/

#include "LimitedCone.hpp"
#include "Rotate3D.hpp"
#include <cmath>

namespace Raytracer {

LimitedCone::LimitedCone(const Math::Point3D& center, const Math::Vector3D& axis, 
    double angle, double height)
    : _center(center), _axis(axis), _angle(angle), _height(height)
{
    double length = std::sqrt(_axis.x * _axis.x + _axis.y * _axis.y + _axis.z * _axis.z);
    if (length > 0)
        _axis = Math::Vector3D(_axis.x / length, _axis.y / length, _axis.z / length);
}

bool LimitedCone::hits(const Ray& ray, HitInfo& hitInfo) const {
    Math::Point3D apex(
        _center.x - _axis.x * _height / 2.0,
        _center.y - _axis.y * _height / 2.0,
        _center.z - _axis.z * _height / 2.0
    );
    Math::Point3D baseCenter(
        _center.x + _axis.x * _height / 2.0,
        _center.y + _axis.y * _height / 2.0,
        _center.z + _axis.z * _height / 2.0
    );

    double radians = _angle * M_PI / 180.0;
    double baseRadius = _height * std::tan(radians);

    const Math::Vector3D& direction = ray._direction;
    const Math::Vector3D& axis = _axis;

    double directionDotAxis = direction.dot(axis);
    if (std::abs(directionDotAxis) > 1e-6) {
        double t = (baseCenter.x - ray._origin.x) * axis.x +
            (baseCenter.y - ray._origin.y) * axis.y + (baseCenter.z - ray._origin.z) * axis.z;
        t /= directionDotAxis;
        if (t > 1e-6) {
            Math::Point3D hitPoint(
                ray._origin.x + t * direction.x,
                ray._origin.y + t * direction.y,
                ray._origin.z + t * direction.z
            );
            Math::Vector3D baseTohit(
                hitPoint.x - baseCenter.x,
                hitPoint.y - baseCenter.y,
                hitPoint.z - baseCenter.z
            );

            double distanceToCenter = std::sqrt(baseTohit.dot(baseTohit));
            if (distanceToCenter <= baseRadius + 1e-6) {
                hitInfo.distance = t;
                hitInfo.point = hitPoint;
                hitInfo.normal = axis;
                
                Math::Vector3D baseTohit(
                    hitPoint.x - baseCenter.x,
                    hitPoint.y - baseCenter.y,
                    hitPoint.z - baseCenter.z
                );
                Math::Vector3D tangent;
                if (std::abs(axis.x) < 0.9) {
                    tangent = Math::Vector3D(0, -axis.z, axis.y);
                } else {
                    tangent = Math::Vector3D(-axis.y, axis.x, 0);
                }
                tangent = tangent.normalize();
                Math::Vector3D bitangent = axis.cross(tangent);
                double x = baseTohit.dot(tangent) / baseRadius;
                double y = baseTohit.dot(bitangent) / baseRadius;
                hitInfo.u = 0.5 + x * 0.5;
                hitInfo.v = 0.5 + y * 0.5;
                return true;
            }
        }
    }

    Math::Vector3D apexToRayOrigin(
        ray._origin.x - apex.x,
        ray._origin.y - apex.y,
        ray._origin.z - apex.z
    );

    double cosSquared = std::cos(radians) * std::cos(radians);
    double tanSquared = std::tan(radians) * std::tan(radians);

    double apexToRayOriginDotAxis = apexToRayOrigin.dot(axis);
    double directionDotDirection = direction.dot(direction);
    double directionDotApexToRayOrigin = direction.dot(apexToRayOrigin);
    double apexToRayOriginDotApexToRayOrigin = apexToRayOrigin.dot(apexToRayOrigin);

    double a = directionDotAxis * directionDotAxis - cosSquared * directionDotDirection;
    double b = 2.0 * (directionDotAxis * apexToRayOriginDotAxis - cosSquared * directionDotApexToRayOrigin);
    double c = apexToRayOriginDotAxis * apexToRayOriginDotAxis - cosSquared * apexToRayOriginDotApexToRayOrigin;

    double determinant = b * b - 4.0 * a * c;
    if (determinant < 0)
        return false;
    
    double determinantRoot = std::sqrt(determinant);
    double solution1 = (-b - determinantRoot) / (2.0 * a);
    double solution2 = (-b + determinantRoot) / (2.0 * a);
    
    double solution = -1;
    if (solution1 > 1e-6 && solution2 > 1e-6)
        solution = std::min(solution1, solution2);
    else if (solution1 > 1e-6)
        solution = solution1;
    else if (solution2 > 1e-6)
        solution = solution2;
    if (solution < 1e-6)
        return false;

    Math::Point3D hitPoint(
        ray._origin.x + solution * direction.x,
        ray._origin.y + solution * direction.y,
        ray._origin.z + solution * direction.z
    );
    Math::Vector3D apexToHit(
        hitPoint.x - apex.x,
        hitPoint.y - apex.y,
        hitPoint.z - apex.z
    );

    double projectionLength = apexToHit.dot(axis);
    if (projectionLength < 0 || projectionLength > _height)
        return false;

    hitInfo.distance = solution;
    hitInfo.point = hitPoint;
    Math::Vector3D normal(
        apexToHit.x - (1.0 + tanSquared) * projectionLength * axis.x,
        apexToHit.y - (1.0 + tanSquared) * projectionLength * axis.y,
        apexToHit.z - (1.0 + tanSquared) * projectionLength * axis.z
    );
    double normalLength = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (normalLength > 0)
        normal = Math::Vector3D(normal.x / normalLength, normal.y / normalLength, normal.z / normalLength);
    hitInfo.normal = normal;
    return true;
}

void LimitedCone::translate(const Math::Vector3D& offset) {
    _center += offset;
}

void LimitedCone::rotateX(double degrees) {
    _axis = Math::rotateVectorX(_axis, degrees);
}

void LimitedCone::rotateY(double degrees) {
    _axis = Math::rotateVectorY(_axis, degrees);
}

void LimitedCone::rotateZ(double degrees) {
    _axis = Math::rotateVectorZ(_axis, degrees);
}

void LimitedCone::scale(double factor) {
    _height *= factor;
}

AABB LimitedCone::getBoundingBox() const {
    double halfHeight = _height / 2.0;
    double baseRadius = std::tan(_angle * M_PI / 180.0) * _height;
    double axisExtent = halfHeight;
    double radialExtent = baseRadius;

    return AABB(
        Math::Point3D(
            _center.x - std::max(axisExtent * std::abs(_axis.x), radialExtent),
            _center.y - std::max(axisExtent * std::abs(_axis.y), radialExtent),
            _center.z - std::max(axisExtent * std::abs(_axis.z), radialExtent)
        ),
        Math::Point3D(
            _center.x + std::max(axisExtent * std::abs(_axis.x), radialExtent),
            _center.y + std::max(axisExtent * std::abs(_axis.y), radialExtent),
            _center.z + std::max(axisExtent * std::abs(_axis.z), radialExtent)
        )
    );
}

}
