/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-bsraytracer-27
** File description:
** main
*/

#include <iostream>
#include "Scene.hpp"
#include "LibConfigSceneBuilder.hpp"
#include "HardCodedSceneBuilder.hpp"
#include "SceneDirector.hpp"
#include "FileWatcher.hpp"
#include "DLloader.hpp"

static void printHelp() {
    std::cout << "USAGE: ./raytracer [SCENE_FILE] [OPTIONS]" << std::endl;
    std::cout << "  SCENE_FILE         scene configuration file (.cfg)" << std::endl;
    std::cout << "  --hardcoded        ignore SCENE_FILE, use built-in test scene" << std::endl;
    std::cout << "  -a <int>           anti-aliasing number of iterations" << std::endl;
    std::cout << "  --help             display this help" << std::endl;
}


int main(int argc, char **argv)
{
    try {

        if (argc == 2 && std::string(argv[1]) == "--help") {
            printHelp();
            return 0;
        }

        bool hardcodedMode = false;
        int antialiasing = 1;
        std::string sceneFilePath;

        for (int i = 1; i < argc; i++) {
            std::string flag = argv[i];
            if (flag == "--help") {
                printHelp();
                return 0;
            }
            if (flag == "--hardcoded")
                hardcodedMode = true;
            else if (flag == "-a") {
                if (i + 1 >= argc) {
                    std::cerr << "Error: -a requires an integer argument." << std::endl;
                    return 84;
                }
                antialiasing = std::stoi(argv[i + 1]);
                i++;
            }
            else if (!flag.empty() && flag[0] != '-' && sceneFilePath.empty())
                sceneFilePath = flag;
            else {
                std::cerr << "Error: Unknown parameter '" << flag << "'." << std::endl;
                return 84;
            }
        }

        if (!hardcodedMode && sceneFilePath.empty()) {
            std::cerr << "Missing scene file." << std::endl;
            return 84;
        }

        Raytracer::ShapeFactory shapeFactory;
        Raytracer::LightFactory lightFactory;

        DLloader shapesPlugin("./plugins/libprimitives.so");
        if (shapesPlugin.isLoaded()) {
            if (auto plugin = shapesPlugin.asShapePlugin()) {
                plugin->registerShapes(shapeFactory);
            }
        }

        if (hardcodedMode) {
            Raytracer::HardCodedSceneBuilder builder(shapeFactory, lightFactory);
            Raytracer::SceneDirector director(builder);

            Raytracer::Scene previewScene;
            director.constructAndRenderPreview(previewScene);
            Raytracer::Scene fullScene;
            director.constructAndRenderFullScene(fullScene, antialiasing);

        } else {
            Raytracer::FileWatcher filewatcher(sceneFilePath);

            while (true) {
                try {
                    Raytracer::LibConfigSceneBuilder builder(sceneFilePath, shapeFactory, lightFactory);
                    Raytracer::SceneDirector director(builder);

                    Raytracer::Scene previewScene;
                    director.constructAndRenderPreview(previewScene);
                    Raytracer::Scene fullScene;
                    director.constructAndRenderFullScene(fullScene, antialiasing);

                } catch (libconfig::SettingTypeException& e) {
                    std::cerr << "Wrong config file syntax: " << e.what() << std::endl;
                } catch (libconfig::SettingNotFoundException& e) {
                    std::cerr << "Config setting not found: " << e.what() << std::endl;
                } catch (std::exception& e) {
                    std::cerr << "Error while rendering: " << e.what() << std::endl;
                }
                
                if (Raytracer::g_cancel_requested)
                    break;
                
                while (!Raytracer::g_cancel_requested) {
                    if (filewatcher.fileChanged()) {
                        break;
                    }
                }
                
                if (Raytracer::g_cancel_requested)
                    break;
            }
        }

        shapeFactory.clearCreators();
        lightFactory.clearCreators();

        return 0;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
}
