/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DLloader
*/

#pragma once
#include <iostream>
#include <dlfcn.h>
#include "IPlugin.hpp"

class DLloader {
public:
    DLloader(const std::string& libpath) : _libpath(libpath), _handle(nullptr), _plugin(nullptr) {
        std::cout << "Loading " << _libpath << std::endl;

        _handle = dlopen(_libpath.c_str(), RTLD_LAZY);
        if (!_handle) {
            std::cerr << "Error: " << dlerror() << std::endl;
            return;
        }

        // Load the plugin factory function
        typedef Raytracer::IPlugin* (*CreatePluginFunc)();
        CreatePluginFunc createPlugin = (CreatePluginFunc)dlsym(_handle, "createPlugin");
        if (!createPlugin) {
            std::cerr << "Error: createPlugin symbol not found" << std::endl;
            dlclose(_handle);
            _handle = nullptr;
            return;
        }

        _plugin = createPlugin();
        std::cout << "Loaded: " << _plugin->getName() << std::endl;
    }

    ~DLloader() {
        if (_plugin) {
            typedef void (*DestroyFunc)(Raytracer::IPlugin*);
            DestroyFunc destroyPlugin = (DestroyFunc)dlsym(_handle, "destroyPlugin");
            if (destroyPlugin) destroyPlugin(_plugin);
        }
        if (_handle) dlclose(_handle);
    }

    // Access plugin by type
    Raytracer::IShapePlugin* asShapePlugin() const {
        if (_plugin && _plugin->getType() == Raytracer::Shape) {
            return dynamic_cast<Raytracer::IShapePlugin*>(_plugin);
        }
        return nullptr;
    }

    Raytracer::ILightPlugin* asLightPlugin() const {
        if (_plugin && _plugin->getType() == Raytracer::Light) {
            return dynamic_cast<Raytracer::ILightPlugin*>(_plugin);
        }
        return nullptr;
    }

    bool isLoaded() const { return _plugin != nullptr; }
    Raytracer::IPlugin* getPlugin() const { return _plugin; }

private:
    std::string _libpath;
    void* _handle;
    Raytracer::IPlugin* _plugin;
};
