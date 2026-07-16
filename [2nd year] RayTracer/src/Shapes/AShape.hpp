/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** AShape
*/

#pragma once
#include "IShape.hpp"
#include <string>

namespace Raytracer {
    class AShape : public IShape {
        public:
            virtual ~AShape() = default;

            AABB getBoundingBox() const override {
                return AABB(
                    Math::Point3D(-1e30, -1e30, -1e30),
                    Math::Point3D( 1e30,  1e30,  1e30)
                );
            }

            void setColor(const Raytracer::Color& color) override { _color = color; }
            Raytracer::Color getColor() const override { return _color; }
            virtual Math::Point3D getReferencePoint() const = 0;
            virtual void setReferencePoint(const Math::Point3D& point) = 0;
            void setFilename(const std::string& filename) override { _file_name = filename; }
            std::string getFilename() const override { return _file_name; }

        private:
            Raytracer::Color _color = Raytracer::Color(1.0, 1.0, 1.0, 1.0);
            std::string _file_name;
    };
}
