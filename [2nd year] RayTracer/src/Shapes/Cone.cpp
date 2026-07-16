/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Cone
*/

#include "Cone.hpp"
#include "Rotate3D.hpp"

namespace Raytracer {

Cone::Cone(const Math::Point3D& apex, const Math::Vector3D& axis, double angle)
    : _apex(apex), _axis(axis), _angle(angle)
{
    double length = std::sqrt(_axis.x * _axis.x + _axis.y * _axis.y + _axis.z * _axis.z);
    if (length > 0)
        _axis = Math::Vector3D(_axis.x / length, _axis.y / length, _axis.z / length);
}

bool Cone::hits(const Ray& ray, HitInfo& hitInfo) const {
    Math::Vector3D apexToRayOrigin(
        ray._origin.x - _apex.x,
        ray._origin.y - _apex.y,
        ray._origin.z - _apex.z
    );

    const Math::Vector3D& direction = ray._direction;
    const Math::Vector3D& axis = _axis;

    double radians = _angle * M_PI / 180.0;
    double cosSquared = std::cos(radians) * std::cos(radians);
    double tanSquared = std::tan(radians) * std::tan(radians);

    double directionDotAxis = direction.dot(axis);
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

    hitInfo.distance = solution;
    hitInfo.point = Math::Point3D(
        ray._origin.x + solution * direction.x,
        ray._origin.y + solution * direction.y,
        ray._origin.z + solution * direction.z
    );
    Math::Vector3D apexToHit(
        hitInfo.point.x - _apex.x,
        hitInfo.point.y - _apex.y,
        hitInfo.point.z - _apex.z
    );

    double projectionLength = apexToHit.dot(axis);
    Math::Vector3D normal(
        apexToHit.x - (1.0 + tanSquared) * projectionLength * axis.x,
        apexToHit.y - (1.0 + tanSquared) * projectionLength * axis.y,
        apexToHit.z - (1.0 + tanSquared) * projectionLength * axis.z
    );

    double normalLength = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (normalLength > 0)
        normal = Math::Vector3D(normal.x / normalLength, normal.y / normalLength, normal.z / normalLength);
    hitInfo.normal = normal;

    hitInfo.v = fmod(projectionLength, 1.0);
    if (hitInfo.v < 0)
        hitInfo.v += 1.0;
    Math::Vector3D radialVector(
        apexToHit.x - projectionLength * axis.x,
        apexToHit.y - projectionLength * axis.y,
        apexToHit.z - projectionLength * axis.z
    );
    Math::Vector3D tangent;
    if (std::abs(axis.x) < 0.9) {
        tangent = Math::Vector3D(0, -axis.z, axis.y);
    } else {
        tangent = Math::Vector3D(-axis.y, axis.x, 0);
    }
    tangent = tangent.normalize();
    Math::Vector3D bitangent = axis.cross(tangent);
    
    double x = radialVector.dot(tangent);
    double y = radialVector.dot(bitangent);
    hitInfo.u = 0.5 + atan2(y, x) / (2.0 * M_PI);
    
    return true;
}

void Cone::translate(const Math::Vector3D& offset) {
    _apex += offset;
}

void Cone::rotateX(double degrees) {
    _axis = Math::rotateVectorX(_axis, degrees);
}

void Cone::rotateY(double degrees) {
    _axis = Math::rotateVectorY(_axis, degrees);
}

void Cone::rotateZ(double degrees) {
    _axis = Math::rotateVectorZ(_axis, degrees);
}

}
