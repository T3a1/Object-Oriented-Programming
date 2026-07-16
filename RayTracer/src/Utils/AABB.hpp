/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** AABB
*/

#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"

namespace Raytracer {
    class AABB {
        public:
            AABB() = default;
            AABB(const Math::Point3D& min, const Math::Point3D& max);

            void expand(const AABB& other);
            void expand(const Math::Point3D& point);
            bool hits(const Ray& ray, double rayDistanceMin, double rayDistanceMax) const;
            Math::Point3D getCenter() const;
            int getLongestAxis() const;

            Math::Point3D _min = Math::Point3D(1e30, 1e30, 1e30);
            Math::Point3D _max = Math::Point3D(-1e30, -1e30, -1e30);
    };
}
