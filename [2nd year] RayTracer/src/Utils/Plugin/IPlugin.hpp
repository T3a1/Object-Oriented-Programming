#pragma once
#include <string>
#include <vector>

namespace Raytracer {

    typedef enum {
        Shape,
        Light
    } PluginType;

    class IPlugin {
    public:
        virtual ~IPlugin() = default;
        virtual const char* getName() const = 0;
        virtual PluginType getType() const = 0;  // "shape" or "light"
        virtual std::vector<std::string> getAvailableItems() const = 0;
    };

    class IShapePlugin : public IPlugin {
    public:
        virtual PluginType getType() const override { return Shape; }
        virtual void registerShapes(class ShapeFactory& factory) = 0;
    };

    class ILightPlugin : public IPlugin {
    public:
        virtual PluginType getType() const override { return Light; }
        virtual void registerLights(class LightFactory& factory) = 0;
    };
}
