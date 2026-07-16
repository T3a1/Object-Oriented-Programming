/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** GroupShape
*/

#pragma once
#include "AShape.hpp"
#include "BVHNode.hpp"
#include <vector>
#include <memory>
#include <string>

namespace Raytracer {
    class GroupShape : public AShape {
        public:
            GroupShape() = default;
            GroupShape(const std::string& name) : _name(name) {}
            ~GroupShape() = default;

            void addShape(const std::shared_ptr<AShape> &shape);
            const std::vector<std::shared_ptr<AShape>> &getShapes() const;

            bool hits(const Ray& ray, HitInfo& hitInfo) const override;
            void translate(const Math::Vector3D& offset) override;
            void rotateX(double degrees) override;
            void rotateY(double degrees) override;
            void rotateZ(double degrees) override;
            void scale(double factor) override;

            void setColor(const Raytracer::Color& color) override;
            Raytracer::Color getColor() const override;

            Math::Point3D getReferencePoint() const override;
            void setReferencePoint(const Math::Point3D& point) override;
            AABB getBoundingBox() const override;
            void buildBVH();

            void setFilename(const std::string& filename) override;
            std::string getFilename() const override;

        private:
            std::vector<std::shared_ptr<AShape>> composingShapes;
            Math::Point3D _referencePoint;
            std::string _name;
            mutable Raytracer::Color _lastHitColor = Raytracer::Color(1.0, 1.0, 1.0, 1.0);
            mutable std::string _lastHitFilename;
            std::shared_ptr<BVHNode> _bvh = nullptr;
    };
}
