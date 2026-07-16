/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** ShapesPlugin
*/

#include "IPlugin.hpp"
#include "ShapeFactory.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cylinder.hpp"
#include "Cone.hpp"
#include "LimitedCylinder.hpp"
#include "LimitedCone.hpp"
#include "Triangle.hpp"
#include <iostream>

namespace Raytracer {

    class BasicShapesPlugin : public IShapePlugin {
    public:
        BasicShapesPlugin() {
            std::cout << "BasicShapesPlugin initialized" << std::endl;
        }
        
        virtual ~BasicShapesPlugin() = default;

        const char* getName() const override {
            return "Basic Primitives";
        }

        std::vector<std::string> getAvailableItems() const override {
            return {"sphere", "plane", "cylinder", "cone", "limited_cylinder", "limited_cone", "triangle"};
        }

        void registerShapes(ShapeFactory& factory) override {
            factory.registerShapeCreator("sphere", []() {
                return std::make_shared<Sphere>();
            });
            
            factory.registerShapeCreator("plane", []() {
                return std::make_shared<Plane>();
            });
            
            factory.registerShapeCreator("cylinder", []() {
                return std::make_shared<Cylinder>();
            });
            
            factory.registerShapeCreator("cone", []() {
                return std::make_shared<Cone>();
            });
            
            factory.registerShapeCreator("limited_cylinder", []() {
                return std::make_shared<LimitedCylinder>();
            });
            
            factory.registerShapeCreator("limited_cone", []() {
                return std::make_shared<LimitedCone>();
            });

            factory.registerShapeCreator("triangle", []() {
                return std::make_shared<Triangle>();
            });
            
            std::cout << "Registered " << getAvailableItems().size() << " shape types" << std::endl;
        }
    };

}

extern "C" {
    
    Raytracer::IPlugin* createPlugin() {
        return new Raytracer::BasicShapesPlugin();
    }
    
    void destroyPlugin(Raytracer::IPlugin* plugin) {
        delete plugin;
    }
}