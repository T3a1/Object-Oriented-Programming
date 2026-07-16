/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-raytracer-9
** File description:
** ObjShape
*/

#include "ObjShape.hpp"
#include "Triangle.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

namespace Raytracer {

ObjShape::ObjShape(const std::string& filePath)
    : GroupShape(filePath)
{
    parseObjFile(filePath);
}

ObjShape::ObjShape(const std::string& filePath, const std::string& mtlPath)
    : GroupShape(filePath)
{
    parseMtlFile(mtlPath);
    parseObjFile(filePath);
}

void ObjShape::parseMtlFile(const std::string& mtlPath) {
    std::ifstream file(mtlPath);
    if (!file.is_open()) {
        std::cerr << "ObjShape: could not open mtl: " << mtlPath << std::endl;
        return;
    }
    std::string line;
    std::string currentMaterial;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream stream(line);
        std::string token;
        stream >> token;
        if (token == "newmtl") {
            stream >> currentMaterial;
            _materials[currentMaterial] = Raytracer::Color(1.0, 1.0, 1.0, 1.0);
        } else if (token == "Kd" && !currentMaterial.empty()) {
            double r;
            double g;
            double b;
            stream >> r >> g >> b;
            _materials[currentMaterial] = Raytracer::Color(r, g, b, 1.0);
        }
    }
}

void ObjShape::parseObjFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "ObjShape: could not open file: " << filePath << std::endl;
        return;
    }

    std::string currentMaterial;
    std::vector<Math::Point3D> vertices;
    std::vector<Math::Vector3D> normals;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream stream(line);
        std::string token;
        stream >> token;

        if (token == "usemtl")
            stream >> currentMaterial;
        else if (token == "v") {
            Math::Point3D vertex;
            stream >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (token == "vn") {
            Math::Vector3D normal;
            stream >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (token == "f") {
            std::vector<int> vertexIndices;
            std::vector<int> normalIndices;

            std::string entry;
            while (stream >> entry) {
                std::replace(entry.begin(), entry.end(), '/', ' ');
                std::istringstream entryStream(entry);
                int vertexIndex = 0;
                int normalIndex = 0;
                entryStream >> vertexIndex;
                entryStream >> normalIndex;
                vertexIndices.push_back(vertexIndex - 1);
                normalIndices.push_back(normalIndex - 1);
            }
            for (int i = 1; i + 1 < (int)vertexIndices.size(); i++) {
                int ia = vertexIndices[0];
                int ib = vertexIndices[i];
                int ic = vertexIndices[i + 1];

                if (ia < 0 || ib < 0 || ic < 0
                    || ia >= (int)vertices.size()
                    || ib >= (int)vertices.size()
                    || ic >= (int)vertices.size())
                    continue;

                auto triangle = std::make_shared<Triangle>(
                    vertices[ia], vertices[ib], vertices[ic]
                );

                if (!normalIndices.empty()
                    && normalIndices[0] >= 0
                    && normalIndices[0] < (int)normals.size()) {
                    triangle->_normal = normals[normalIndices[0]];
                }
                if (!currentMaterial.empty() && _materials.count(currentMaterial))
                    triangle->setColor(_materials.at(currentMaterial));
                addShape(triangle);
            }
        }
    }
    if (!vertices.empty()) {
        double cx = 0;
        double cy = 0;
        double cz = 0;
        for (const auto& v : vertices) {
            cx += v.x;
            cy += v.y;
            cz += v.z;
        }
        cx /= vertices.size();
        cy /= vertices.size();
        cz /= vertices.size();
        setReferencePoint(Math::Point3D(cx, cy, cz));
    }
    std::cout << "ObjShape: loaded " << getShapes().size()
        << "triangles from " << filePath << std::endl;
}

}
