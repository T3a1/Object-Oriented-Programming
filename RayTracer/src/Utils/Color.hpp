/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** color
*/

#pragma once
#include "Vector3D.hpp"
#include <iostream>
#include <tuple>

namespace Raytracer {
    class Color {
        public:
            Color() : r(0), g(0), b(0), a(1) {}
            Color(double red, double green, double blue, double alpha)
                : r(red), g(green), b(blue), a(alpha) {}
            Color(const Math::Vector3D& rgb, double alpha = 1.0)
                : r(rgb.x), g(rgb.y), b(rgb.z), a(alpha) {}
            operator Math::Vector3D() const {
                return Math::Vector3D(r, g, b);
            }
            void setColor(double red, double green, double blue, double alpha) {
                r = red;
                g = green;
                b = blue;
                a = alpha;
            }
            std::tuple<double, double, double, double> getColor() const {
                return std::make_tuple(r, g, b, a);
            }
        private:
            double r;
            double g;
            double b;
            double a;
    };

    inline void write_color(const Math::Vector3D& color)
    {
        int r = static_cast<int>(color.x * 255.0);
        int g = static_cast<int>(color.y * 255.0);
        int b = static_cast<int>(color.z * 255.0);

        std::cout << r << " " << g << " " << b << "\n";
    }

    inline void write_color(const Color& color)
    {
        std::tuple<double, double, double, double> rgba = color.getColor();

        int r = static_cast<int>(std::get<0>(rgba) * 255.0);
        int g = static_cast<int>(std::get<1>(rgba) * 255.0);
        int b = static_cast<int>(std::get<2>(rgba) * 255.0);
        int a = static_cast<int>(std::get<3>(rgba) * 255.0);
        
        std::cout << r << " " << g << " " << b << " " << a << "\n";
    }
}
