/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** Plane
*/

#include "Plane.hpp"
#include "Rotate3D.hpp"
#include <cmath>

namespace Raytracer {

Plane::Plane(const Math::Point3D& point, const Math::Vector3D& normal)
    : _point(point), _normal(normal)
{
    double len = _normal.length();
    if (len > 0) {
        _normal.x /= len;
        _normal.y /= len;
        _normal.z /= len;
    }
}

bool Plane::hits(const Ray& ray, HitInfo& hitInfo) const {
    
    double denominator = ray._direction.dot(_normal);
    
    if (std::abs(denominator) < 1e-6)
        return false;

    Math::Vector3D toPoint(_point.x - ray._origin.x,
        _point.y - ray._origin.y, _point.z - ray._origin.z);
    
    double t = toPoint.dot(_normal) / denominator;
    if (t < 1e-6)
        return false;
    hitInfo.distance = t;
    hitInfo.point = Math::Point3D(
        ray._origin.x + t * ray._direction.x,
        ray._origin.y + t * ray._direction.y,
        ray._origin.z + t * ray._direction.z
    );
    hitInfo.normal = _normal;

    Math::Vector3D tangent1;
    if (std::abs(_normal.x) < 0.9) {
        tangent1 = Math::Vector3D(0, -_normal.z, _normal.y);
    } else {
        tangent1 = Math::Vector3D(-_normal.y, _normal.x, 0);
    }
    tangent1 = tangent1.normalize();
    Math::Vector3D tangent2 = _normal.cross(tangent1);
    tangent2 = tangent2.normalize();
    Math::Vector3D fromPoint(_point.x - hitInfo.point.x, _point.y - hitInfo.point.y, _point.z - hitInfo.point.z);
    hitInfo.u = fmod(fromPoint.dot(tangent1) / 5.0, 1.0);
    hitInfo.v = fmod(fromPoint.dot(tangent2) / 5.0, 1.0);
    
    if (hitInfo.u < 0)
        hitInfo.u += 1.0;
    if (hitInfo.v < 0)
        hitInfo.v += 1.0;
    
    return true;
}

void Plane::translate(const Math::Vector3D& offset) {
    _point += offset;
}

void Plane::rotateX(double degrees) {
    _normal = Math::rotateVectorX(_normal, degrees);
}

void Plane::rotateY(double degrees) {
    _normal = Math::rotateVectorY(_normal, degrees);
}

void Plane::rotateZ(double degrees) {
    _normal = Math::rotateVectorZ(_normal, degrees);
}

}
