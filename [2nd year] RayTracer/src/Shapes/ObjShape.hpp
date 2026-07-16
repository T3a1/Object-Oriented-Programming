/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** ObjShape
*/

#pragma once
#include "GroupShape.hpp"
#include <string>
#include <map>

namespace Raytracer {
    class ObjShape : public GroupShape {
        public:
            ObjShape() = default;
            ObjShape(const std::string& filePath);
            ObjShape(const std::string& filePath, const std::string& mtlPath);
            ~ObjShape() = default;

        private:
            std::map<std::string, Raytracer::Color> _materials;

            void parseObjFile(const std::string& filePath);
            void parseMtlFile(const std::string& mtlPath);
    };
}
