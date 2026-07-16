/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** GroupShape
*/
#include "GroupShape.hpp"
#include "Rotate3D.hpp"
#include <cmath>
#include <limits>

namespace Raytracer {

void GroupShape::addShape(const std::shared_ptr<AShape> &shape) {
    composingShapes.push_back(shape);
}

const std::vector<std::shared_ptr<AShape>> &GroupShape::getShapes() const {
    return composingShapes;
}

void GroupShape::buildBVH() {
    if (composingShapes.empty())
        return;

    std::vector<std::shared_ptr<IShape>> shapes(
        composingShapes.begin(), composingShapes.end()
    );

    _bvh = std::make_shared<BVHNode>();
    _bvh->build(shapes, 0, shapes.size());
}

bool GroupShape::hits(const Ray& ray, HitInfo& hitInfo) const {
    if (_bvh)
        return _bvh->hits(ray, hitInfo);

    double closestDistance = std::numeric_limits<double>::infinity();
    bool hit = false;

    for (const auto& shape : composingShapes) {
        HitInfo tempHitInfo;
        if (shape->hits(ray, tempHitInfo)) {
            hit = true;
            if (tempHitInfo.distance < closestDistance) {
                closestDistance = tempHitInfo.distance;
                hitInfo = tempHitInfo;
                _lastHitColor = shape->getColor();
                _lastHitFilename = shape->getFilename();
            }
        }
    }
    return hit;
}

void GroupShape::translate(const Math::Vector3D& offset) {
    _referencePoint += offset;
    for (const auto& shape : composingShapes)
        shape->translate(offset);
}

void GroupShape::rotateX(double degrees) {
    for (const auto& shape : composingShapes) {
        shape->setReferencePoint(Math::rotatePointX(shape->getReferencePoint(), _referencePoint, degrees));
        shape->rotateX(degrees);
    }
}

void GroupShape::rotateY(double degrees) {
    for (const auto& shape : composingShapes) {
        shape->setReferencePoint(Math::rotatePointY(shape->getReferencePoint(), _referencePoint, degrees));
        shape->rotateY(degrees);
    }
}

void GroupShape::rotateZ(double degrees) {
    for (const auto& shape : composingShapes) {
        shape->setReferencePoint(Math::rotatePointZ(shape->getReferencePoint(), _referencePoint, degrees));
        shape->rotateZ(degrees);
    }
}

void GroupShape::scale(double factor) {
    for (const auto& shape : composingShapes) {
        Math::Point3D referencePoint = shape->getReferencePoint();
        Math::Vector3D distance(referencePoint.x - _referencePoint.x,
            referencePoint.y - _referencePoint.y,
            referencePoint.z - _referencePoint.z
        );

        shape->setReferencePoint(Math::Point3D(
            _referencePoint.x + distance.x * factor,
            _referencePoint.y + distance.y * factor,
            _referencePoint.z + distance.z * factor
        ));
        shape->scale(factor);
    }
}

void GroupShape::setColor(const Raytracer::Color& color) {
    for (const auto& shape : composingShapes)
        shape->setColor(color);
}

Raytracer::Color GroupShape::getColor() const {
    return _lastHitColor;
}

Math::Point3D GroupShape::getReferencePoint() const {
    return _referencePoint;
}

void GroupShape::setReferencePoint(const Math::Point3D& point) {
    _referencePoint = point;
}

void GroupShape::setFilename(const std::string& filename) {
    for (const auto& shape : composingShapes)
        shape->setFilename(filename);
}

std::string GroupShape::getFilename() const {
    return _lastHitFilename;
}

AABB GroupShape::getBoundingBox() const {
    if (composingShapes.empty())
        return AABB();

    AABB groupBox = composingShapes[0]->getBoundingBox();

    for (size_t i = 1; i < composingShapes.size(); i++)
        groupBox.expand(composingShapes[i]->getBoundingBox());
    return groupBox;
}

}
