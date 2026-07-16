/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "Rotate3D.hpp"
#include <cmath>
#include <algorithm>

namespace Raytracer {

Triangle::Triangle(const Math::Point3D &a, const Math::Point3D &b, const Math::Point3D &c)
    : _a(a), _b(b), _c(c)
{
    _center = Math::Point3D(
        (_a.x + _b.x + _c.x) / 3.0,
        (_a.y + _b.y + _c.y) / 3.0,
        (_a.z + _b.z + _c.z) / 3.0
    );
    computeNormal();
}

bool Triangle::hits(const Ray& ray, HitInfo& hitInfo) const {
    Math::Vector3D edgeAB(_b.x - _a.x, _b.y - _a.y, _b.z - _a.z);
    Math::Vector3D edgeAC(_c.x - _a.x, _c.y - _a.y, _c.z - _a.z);
    Math::Vector3D rayCrossEdgeAC(
        ray._direction.y * edgeAC.z - ray._direction.z * edgeAC.y,
        ray._direction.z * edgeAC.x - ray._direction.x * edgeAC.z,
        ray._direction.x * edgeAC.y - ray._direction.y * edgeAC.x
    );

    double determinant = edgeAB.dot(rayCrossEdgeAC);
    if (std::abs(determinant) < 1e-6)
        return false;

    double inverseDeterminant = 1.0 / determinant;
    Math::Vector3D vertexAToRayOrigin(ray._origin.x - _a.x, ray._origin.y - _a.y, ray._origin.z - _a.z);
    double barycentricU = inverseDeterminant * vertexAToRayOrigin.dot(rayCrossEdgeAC);
    if (barycentricU < 0.0 || barycentricU > 1.0)
        return false;

    Math::Vector3D vertexAToRayOriginCrossEdgeAB(
        vertexAToRayOrigin.y * edgeAB.z - vertexAToRayOrigin.z * edgeAB.y,
        vertexAToRayOrigin.z * edgeAB.x - vertexAToRayOrigin.x * edgeAB.z,
        vertexAToRayOrigin.x * edgeAB.y - vertexAToRayOrigin.y * edgeAB.x
    );
    double barycentricV = inverseDeterminant * ray._direction.dot(vertexAToRayOriginCrossEdgeAB);
    if (barycentricV < 0.0 || barycentricU + barycentricV > 1.0)
        return false;

    double rayDistance = inverseDeterminant * edgeAC.dot(vertexAToRayOriginCrossEdgeAB);
    if (rayDistance > 1e-6) {
        hitInfo.distance = rayDistance;
        hitInfo.point = Math::Point3D(
            ray._origin.x + rayDistance * ray._direction.x,
            ray._origin.y + rayDistance * ray._direction.y,
            ray._origin.z + rayDistance * ray._direction.z
        );
        hitInfo.normal = _normal;
        hitInfo.u = barycentricU;
        hitInfo.v = barycentricV;
        return true;
    }
    return false;
}

void Triangle::translate(const Math::Vector3D& offset) {
    _a += offset;
    _b += offset;
    _c += offset;
    _center += offset;
}

void Triangle::rotateX(double degrees) {
    _a = Math::rotatePointX(_a, _center, degrees);
    _b = Math::rotatePointX(_b, _center, degrees);
    _c = Math::rotatePointX(_c, _center, degrees);

    computeNormal();
}

void Triangle::rotateY(double degrees) {
    _a = Math::rotatePointY(_a, _center, degrees);
    _b = Math::rotatePointY(_b, _center, degrees);
    _c = Math::rotatePointY(_c, _center, degrees);

    computeNormal();
}

void Triangle::rotateZ(double degrees) {
    _a = Math::rotatePointZ(_a, _center, degrees);
    _b = Math::rotatePointZ(_b, _center, degrees);
    _c = Math::rotatePointZ(_c, _center, degrees);

    computeNormal();
}

void Triangle::scale(double factor) {
    auto scalePoint = [&](Math::Point3D& point) {
        point.x = _center.x + (point.x - _center.x) * factor;
        point.y = _center.y + (point.y - _center.y) * factor;
        point.z = _center.z + (point.z - _center.z) * factor;
    };
    scalePoint(_a);
    scalePoint(_b);
    scalePoint(_c);

    computeNormal();
}

void Triangle::setReferencePoint(const Math::Point3D& point) {
    Math::Vector3D offset(point.x - _center.x, point.y - _center.y, point.z - _center.z);
    translate(offset);
}

void Triangle::computeNormal() {
    Math::Vector3D edgeAB(_b.x - _a.x, _b.y - _a.y, _b.z - _a.z);
    Math::Vector3D edgeAC(_c.x - _a.x, _c.y - _a.y, _c.z - _a.z);

    _normal = Math::Vector3D(
        edgeAB.y * edgeAC.z - edgeAB.z * edgeAC.y,
        edgeAB.z * edgeAC.x - edgeAB.x * edgeAC.z,
        edgeAB.x * edgeAC.y - edgeAB.y * edgeAC.x
    );

    double length = std::sqrt(_normal.x * _normal.x + _normal.y * _normal.y + _normal.z * _normal.z);
    if (length > 0)
        _normal = Math::Vector3D(_normal.x / length, _normal.y / length, _normal.z / length);
}

AABB Triangle::getBoundingBox() const {
    return AABB(
        Math::Point3D(
            std::min({_a.x, _b.x, _c.x}) - 1e-4,
            std::min({_a.y, _b.y, _c.y}) - 1e-4,
            std::min({_a.z, _b.z, _c.z}) - 1e-4
        ),
        Math::Point3D(
            std::max({_a.x, _b.x, _c.x}) + 1e-4,
            std::max({_a.y, _b.y, _c.y}) + 1e-4,
            std::max({_a.z, _b.z, _c.z}) + 1e-4
        )
    );
}

}
