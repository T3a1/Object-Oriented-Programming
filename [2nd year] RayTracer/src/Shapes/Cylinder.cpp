/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "Rotate3D.hpp"

namespace Raytracer {

Cylinder::Cylinder(const Math::Point3D& baseCenter, const Math::Vector3D& axis, double radius)
    : _baseCenter(baseCenter), _axis(axis), _radius(radius)
{
    double length = std::sqrt(_axis.x * _axis.x + _axis.y * _axis.y + _axis.z * _axis.z);
    if (length > 0)
        _axis = Math::Vector3D(_axis.x / length, _axis.y / length, _axis.z / length);
}

bool Cylinder::hits(const Ray& ray, HitInfo& hitInfo) const {
    Math::Vector3D baseToRayOrigin(
        ray._origin.x - _baseCenter.x,
        ray._origin.y - _baseCenter.y,
        ray._origin.z - _baseCenter.z
    );

    const Math::Vector3D& direction = ray._direction;
    const Math::Vector3D& axis = _axis;

    double directionDotAxis = direction.dot(axis);
    Math::Vector3D directionPerpendicular = direction - axis * directionDotAxis;
    double baseToRayOriginDotAxis = baseToRayOrigin.dot(axis);
    Math::Vector3D baseToRayOriginPerpendicular = baseToRayOrigin - axis * baseToRayOriginDotAxis;

    double a = directionPerpendicular.dot(directionPerpendicular);
    double b = 2 * directionPerpendicular.dot(baseToRayOriginPerpendicular);
    double c = baseToRayOriginPerpendicular.dot(baseToRayOriginPerpendicular) - _radius * _radius;
    double determinant = b * b - 4.0 * a * c;

    double rootDiscriminant = std::sqrt(determinant);
    double solution1 = (-b - rootDiscriminant) / (2.0 * a);
    double solution2 = (-b + rootDiscriminant) / (2.0 * a);

    double solution = -1.0;
    if (solution1 > 1e-6)
        solution = solution1;
    else if (solution2 > 1e-6)
        solution = solution2;
    else
        return false;

    hitInfo.distance = solution;
    hitInfo.point = Math::Point3D(
        ray._origin.x + solution * direction.x,
        ray._origin.y + solution * direction.y,
        ray._origin.z + solution * direction.z
    );
    Math::Vector3D hitToBase(
        hitInfo.point.x - _baseCenter.x,
        hitInfo.point.y - _baseCenter.y,
        hitInfo.point.z - _baseCenter.z
    );
    double projectionLength = hitToBase.dot(axis);
    Math::Point3D projectionPoint(
        _baseCenter.x + projectionLength * axis.x,
        _baseCenter.y + projectionLength * axis.y,
        _baseCenter.z + projectionLength * axis.z
    );
    hitInfo.normal = Math::Vector3D(
        (hitInfo.point.x - projectionPoint.x) / _radius,
        (hitInfo.point.y - projectionPoint.y) / _radius,
        (hitInfo.point.z - projectionPoint.z) / _radius
    );
    
    Math::Vector3D toHit(
        hitInfo.point.x - _baseCenter.x,
        hitInfo.point.y - _baseCenter.y,
        hitInfo.point.z - _baseCenter.z
    );
    double projectedLength = toHit.dot(_axis);
    hitInfo.v = fmod(projectedLength, 1.0);
    if (hitInfo.v < 0)
        hitInfo.v += 1.0;

    Math::Vector3D radialVector(
        hitInfo.point.x - projectionPoint.x,
        hitInfo.point.y - projectionPoint.y,
        hitInfo.point.z - projectionPoint.z
    );
    Math::Vector3D tangent;
    if (std::abs(_axis.x) < 0.9) {
        tangent = Math::Vector3D(0, -_axis.z, _axis.y);
    } else {
        tangent = Math::Vector3D(-_axis.y, _axis.x, 0);
    }
    tangent = tangent.normalize();
    Math::Vector3D bitangent = _axis.cross(tangent);
    
    double x = radialVector.dot(tangent) / _radius;
    double y = radialVector.dot(bitangent) / _radius;
    hitInfo.u = 0.5 + atan2(y, x) / (2.0 * M_PI);
    
    return true;
}

void Cylinder::translate(const Math::Vector3D& offset) {
    _baseCenter += offset;
}

void Cylinder::rotateX(double degrees) {
    _axis = Math::rotateVectorX(_axis, degrees);
}

void Cylinder::rotateY(double degrees) {
    _axis = Math::rotateVectorY(_axis, degrees);
}

void Cylinder::rotateZ(double degrees) {
    _axis = Math::rotateVectorZ(_axis, degrees);
}

void Cylinder::scale(double factor) {
    _radius *= factor;
}

}
