/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** IShape interface
*/

#pragma once
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "HitInfo.hpp"
#include "Color.hpp"
#include "AABB.hpp"
#include <string>

namespace Raytracer {
    class IShape {
        public:
            virtual ~IShape() = default;
            virtual bool hits(const Ray& ray, HitInfo& hitInfo) const = 0;
            virtual void translate(const Math::Vector3D& offset) = 0;
            virtual void rotateX(double degrees) = 0;
            virtual void rotateY(double degrees) = 0;
            virtual void rotateZ(double degrees) = 0;
            virtual void scale(double factor) = 0;
            virtual AABB getBoundingBox() const = 0;
            virtual void setColor(const Raytracer::Color& color) = 0;
            virtual Raytracer::Color getColor() const = 0;
            virtual void setFilename(const std::string& filename) = 0;
            virtual std::string getFilename() const = 0;
    };
}
