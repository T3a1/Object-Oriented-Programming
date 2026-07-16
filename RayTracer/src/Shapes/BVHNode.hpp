/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** BVHNode
*/

#pragma once
#include "IShape.hpp"
#include "AABB.hpp"
#include <memory>
#include <vector>

namespace Raytracer {
    class BVHNode : public IShape {
        public:
            BVHNode() = default;

            void build(std::vector<std::shared_ptr<IShape>>& shapes, int start, int end);
            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            AABB getBoundingBox() const override { return _box; }

            void translate(const Math::Vector3D&) override {}
            void rotateX(double) override {}
            void rotateY(double) override {}
            void rotateZ(double) override {}
            void scale(double) override {}
            void setColor(const Raytracer::Color&) override {}
            Raytracer::Color getColor() const override { return Raytracer::Color(1,1,1,1); }
            void setFilename(const std::string&) override {}
            std::string getFilename() const override { return ""; }

        private:
            std::shared_ptr<IShape> _left;
            std::shared_ptr<IShape> _right;
            AABB _box;
    };
}
