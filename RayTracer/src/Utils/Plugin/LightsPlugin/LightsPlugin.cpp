/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** LightsPlugin
*/

#include "IPlugin.hpp"
#include "LightFactory.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include <iostream>

namespace Raytracer {

    class StandardLightsPlugin : public ILightPlugin {
    public:
        StandardLightsPlugin() {
            std::cout << "StandardLightsPlugin initialized" << std::endl;
        }
        
        virtual ~StandardLightsPlugin() = default;

        const char* getName() const override {
            return "Standard Lights";
        }

        std::vector<std::string> getAvailableItems() const override {
            return {"ambient", "directional", "point"};
        }

        void registerLights(LightFactory& factory) override {
            factory.registerLightCreator("ambient", []() {
                return std::make_unique<AmbientLight>();
            });
            
            factory.registerLightCreator("directional", []() {
                return std::make_unique<DirectionalLight>();
            });
            
            factory.registerLightCreator("point", []() {
                return std::make_unique<PointLight>();
            });
            
            std::cout << "Registered " << getAvailableItems().size() << " light types" << std::endl;
        }
    };

}

extern "C" {
    
    Raytracer::IPlugin* createPlugin() {
        return new Raytracer::StandardLightsPlugin();
    }
    
    void destroyPlugin(Raytracer::IPlugin* plugin) {
        delete plugin;
    }
}
