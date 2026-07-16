/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** BVHNode
*/

#include "BVHNode.hpp"
#include <algorithm>

namespace Raytracer {

void BVHNode::build(std::vector<std::shared_ptr<IShape>>& shapes, int start, int end) {
    _box = shapes[start]->getBoundingBox();
    for (int i = start + 1; i < end; i++)
        _box.expand(shapes[i]->getBoundingBox());

    int count = end - start;

    if (count == 1) {
        _left = shapes[start];
        _right = _left;
    } else if (count == 2) {
        _left = shapes[start];
        _right = shapes[start + 1];
    } else {
        int axis = _box.getLongestAxis();

        std::sort(shapes.begin() + start, shapes.begin() + end,
            [axis](const std::shared_ptr<IShape>& a, const std::shared_ptr<IShape>& b)
        {
            AABB boxA = a->getBoundingBox();
            AABB boxB = b->getBoundingBox();
            double centroidA = (axis == 0) ? boxA.getCenter().x
                : (axis == 1) ? boxA.getCenter().y : boxA.getCenter().z;
            double centroidB = (axis == 0) ? boxB.getCenter().x
                : (axis == 1) ? boxB.getCenter().y : boxB.getCenter().z;
            return centroidA < centroidB;
        });

        int mid = start + count / 2;
        auto leftNode = std::make_shared<BVHNode>();
        auto rightNode = std::make_shared<BVHNode>();
        leftNode->build(shapes, start, mid);
        rightNode->build(shapes, mid, end);
        _left = leftNode;
        _right = rightNode;
    }
}

bool BVHNode::hits(const Ray& ray, HitInfo& hitInfo) const {
    if (!_box.hits(ray, 1e-6, std::numeric_limits<double>::infinity()))
        return false;

    HitInfo leftHit;
    HitInfo rightHit;
    bool hitLeft = _left->hits(ray, leftHit);
    bool hitRight = _right->hits(ray, rightHit);

    if (hitLeft && hitRight) {
        hitInfo = (leftHit.distance < rightHit.distance) ? leftHit : rightHit;
        return true;
    }
    if (hitLeft)  {
        hitInfo = leftHit; 
        return true;
    }
    if (hitRight) {
        hitInfo = rightHit;
        return true;
    }
    return false;
}

}
