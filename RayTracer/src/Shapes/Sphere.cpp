/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <cmath>

namespace Raytracer {

Sphere::Sphere(const Math::Point3D &center, double radius)
    : _center(center), _radius(radius)
{

}

bool Sphere::hits(const Ray& ray, HitInfo& hitInfo) const {
    Math::Vector3D vector = Math::Vector3D(ray._origin.x - _center.x, ray._origin.y - _center.y, ray._origin.z - _center.z);
    double a = ray._direction.dot(ray._direction);
    double b = vector.dot(ray._direction) * 2.0;
    double c = vector.dot(vector) - _radius * _radius;
    double determinant = b * b - 4 * a * c;

    if (determinant < 0)
        return false;

    double solution1 = (-b - std::sqrt(determinant)) / (2 * a);
    double solution2 = (-b + std::sqrt(determinant)) / (2 * a);
    if (solution1 < 1e-6 && solution2 < 1e-6)
        return false;

    hitInfo.distance = solution1 > 1e-6 ? solution1 : solution2;
    hitInfo.point = Math::Point3D(
        ray._origin.x + hitInfo.distance * ray._direction.x,
        ray._origin.y + hitInfo.distance * ray._direction.y,
        ray._origin.z + hitInfo.distance * ray._direction.z
    );
    hitInfo.normal = Math::Vector3D(
        (hitInfo.point.x - _center.x) / _radius,
        (hitInfo.point.y - _center.y) / _radius,
        (hitInfo.point.z - _center.z) / _radius
    );

    double dx = (hitInfo.point.x - _center.x) / _radius;
    double dy = (hitInfo.point.y - _center.y) / _radius;
    double dz = (hitInfo.point.z - _center.z) / _radius;

    hitInfo.u = 0.5 + atan2(dz, dx) / (2.0 * M_PI);

    double dy_clamped = (dy < -1.0) ? -1.0 : (dy > 1.0) ? 1.0 : dy;
    hitInfo.v = 0.5 - asin(dy_clamped) / M_PI;
    
    return true;
}

void Sphere::translate(const Math::Vector3D& offset) {
    _center += offset;
}

void Sphere::rotateX(double degrees) {
    (void)degrees;
}

void Sphere::rotateY(double degrees) {
    (void)degrees;
}

void Sphere::rotateZ(double degrees) {
    (void)degrees;
}

void Sphere::scale(double factor) {
    _radius *= factor;
}

AABB Sphere::getBoundingBox() const {
    return AABB(
        Math::Point3D(_center.x - _radius, _center.y - _radius, _center.z - _radius),
        Math::Point3D(_center.x + _radius, _center.y + _radius, _center.z + _radius)
    );
}

}
