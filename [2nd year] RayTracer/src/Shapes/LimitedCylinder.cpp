/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Limited Cylinder
*/

#include "LimitedCylinder.hpp"
#include "Rotate3D.hpp"
#include <cmath>
#include <limits>

namespace Raytracer {

LimitedCylinder::LimitedCylinder(const Math::Point3D& center, const Math::Vector3D& axis,
    double radius, double height)
    : _center(center), _axis(axis), _radius(radius), _height(height)
{
    double length = std::sqrt(_axis.x * _axis.x + _axis.y * _axis.y + _axis.z * _axis.z);
    if (length > 0)
        _axis = Math::Vector3D(_axis.x / length, _axis.y / length, _axis.z / length);
}

bool LimitedCylinder::hits(const Ray& ray, HitInfo& hitInfo) const {
    const Math::Vector3D& direction = ray._direction;
    const Math::Vector3D& axis = _axis;

    Math::Point3D baseCenter(
        _center.x - axis.x * _height / 2.0,
        _center.y - axis.y * _height / 2.0,
        _center.z - axis.z * _height / 2.0
    );
    Math::Point3D topCenter(
        _center.x + axis.x * _height / 2.0,
        _center.y + axis.y * _height / 2.0,
        _center.z + axis.z * _height / 2.0
    );

    double closestDistance = std::numeric_limits<double>::max();
    bool hitFound = false;
    HitInfo closestHit;

    double directionDotAxis = direction.dot(axis);

    auto checkCapHit = [&](const Math::Point3D& capCenter, int normalDirection) {
        if (std::abs(directionDotAxis) > 1e-6) {
            double t = (capCenter.x - ray._origin.x) * axis.x
                + (capCenter.y - ray._origin.y) * axis.y + (capCenter.z - ray._origin.z) * axis.z;
            t /= directionDotAxis;

            if (t > 1e-6) {
                Math::Point3D hitPoint(
                    ray._origin.x + t * direction.x,
                    ray._origin.y + t * direction.y,
                    ray._origin.z + t * direction.z
                );
                Math::Vector3D capToHit(
                    hitPoint.x - capCenter.x,
                    hitPoint.y - capCenter.y,
                    hitPoint.z - capCenter.z
                );

                double distanceToCenter = std::sqrt(capToHit.dot(capToHit));
                if (distanceToCenter <= _radius + 1e-6 && t < closestDistance) {
                    closestDistance = t;
                    closestHit.distance = t;
                    closestHit.point = hitPoint;
                    closestHit.normal = axis * (directionDotAxis < 0 ? normalDirection : -normalDirection);

                    Math::Vector3D tangent;
                    if (std::abs(axis.x) < 0.9) {
                        tangent = Math::Vector3D(0, -axis.z, axis.y);
                    } else {
                        tangent = Math::Vector3D(-axis.y, axis.x, 0);
                    }
                    tangent = tangent.normalize();
                    Math::Vector3D bitangent = axis.cross(tangent);
                    double x = capToHit.dot(tangent) / _radius;
                    double y = capToHit.dot(bitangent) / _radius;
                    closestHit.u = 0.5 + x * 0.5;
                    closestHit.v = 0.5 + y * 0.5;
                    hitFound = true;
                }
            }
        }
    };
    checkCapHit(baseCenter, 1);
    checkCapHit(topCenter, -1);

    Math::Vector3D baseToRayOrigin(
        ray._origin.x - baseCenter.x,
        ray._origin.y - baseCenter.y,
        ray._origin.z - baseCenter.z
    );

    double directionPerpendicular_dot = direction.dot(direction) - directionDotAxis * directionDotAxis;
    Math::Vector3D directionPerpendicular(
        direction.x - axis.x * directionDotAxis,
        direction.y - axis.y * directionDotAxis,
        direction.z - axis.z * directionDotAxis
    );
    double baseToRayOriginDotAxis = baseToRayOrigin.dot(axis);
    Math::Vector3D baseToRayOriginPerpendicular(
        baseToRayOrigin.x - axis.x * baseToRayOriginDotAxis,
        baseToRayOrigin.y - axis.y * baseToRayOriginDotAxis,
        baseToRayOrigin.z - axis.z * baseToRayOriginDotAxis
    );

    double a = directionPerpendicular_dot;
    double b = 2 * directionPerpendicular.dot(baseToRayOriginPerpendicular);
    double c = baseToRayOriginPerpendicular.dot(baseToRayOriginPerpendicular) - _radius * _radius;
    double determinant = b * b - 4.0 * a * c;

    if (determinant >= 0) {
        double rootDiscriminant = std::sqrt(determinant);
        double solution1 = (-b - rootDiscriminant) / (2.0 * a);
        double solution2 = (-b + rootDiscriminant) / (2.0 * a);

        double solution = -1.0;
        if (solution1 > 1e-6)
            solution = solution1;
        else if (solution2 > 1e-6)
            solution = solution2;

        if (solution > 1e-6) {
            Math::Point3D hitPoint(
                ray._origin.x + solution * direction.x,
                ray._origin.y + solution * direction.y,
                ray._origin.z + solution * direction.z
            );
            Math::Vector3D hitToBase(
                hitPoint.x - baseCenter.x,
                hitPoint.y - baseCenter.y,
                hitPoint.z - baseCenter.z
            );

            double projectionLength = hitToBase.dot(axis);
            if (projectionLength >= 0 && projectionLength <= _height) {
                if (solution < closestDistance) {
                    closestDistance = solution;
                    closestHit.distance = solution;
                    closestHit.point = hitPoint;
                    
                    Math::Point3D projectionPoint(
                        baseCenter.x + projectionLength * axis.x,
                        baseCenter.y + projectionLength * axis.y,
                        baseCenter.z + projectionLength * axis.z
                    );
                    closestHit.normal = Math::Vector3D(
                        (hitPoint.x - projectionPoint.x) / _radius,
                        (hitPoint.y - projectionPoint.y) / _radius,
                        (hitPoint.z - projectionPoint.z) / _radius
                    );
                    
                    closestHit.v = projectionLength / _height;
                    
                    Math::Vector3D radialVector(
                        hitPoint.x - projectionPoint.x,
                        hitPoint.y - projectionPoint.y,
                        hitPoint.z - projectionPoint.z
                    );
                    
                    Math::Vector3D tangent;
                    if (std::abs(axis.x) < 0.9) {
                        tangent = Math::Vector3D(0, -axis.z, axis.y);
                    } else {
                        tangent = Math::Vector3D(-axis.y, axis.x, 0);
                    }
                    tangent = tangent.normalize();
                    
                    Math::Vector3D bitangent = axis.cross(tangent);
                    
                    double x = radialVector.dot(tangent) / _radius;
                    double y = radialVector.dot(bitangent) / _radius;
                    closestHit.u = 0.5 + atan2(y, x) / (2.0 * M_PI);
                    
                    hitFound = true;
                }
            }
        }
    }
    if (hitFound) {
        hitInfo = closestHit;
        return true;
    }
    return false;
}

void LimitedCylinder::translate(const Math::Vector3D& offset) {
    _center += offset;
}

void LimitedCylinder::rotateX(double degrees) {
    _axis = Math::rotateVectorX(_axis, degrees);
}

void LimitedCylinder::rotateY(double degrees) {
    _axis = Math::rotateVectorY(_axis, degrees);
}

void LimitedCylinder::rotateZ(double degrees) {
    _axis = Math::rotateVectorZ(_axis, degrees);
}

void LimitedCylinder::scale(double factor) {
    _radius *= factor;
    _height *= factor;
}

AABB LimitedCylinder::getBoundingBox() const {
    double halfHeight = _height / 2.0;
    double extent = std::max(_radius, halfHeight);

    return AABB(
        Math::Point3D(_center.x - extent, _center.y - extent, _center.z - extent),
        Math::Point3D(_center.x + extent, _center.y + extent, _center.z + extent)
    );
}

}
