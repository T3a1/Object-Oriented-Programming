/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** main
*/

#include "Core.hpp"
#include "ArcError.hpp"
#include <filesystem>
#include <set>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <renderer_library>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string rendererLibPath = argv[1];
    if (rendererLibPath.substr(0, 2) == "./")
        rendererLibPath = rendererLibPath.substr(2);

    try {
        Arc::Core::validateDefaultRenderer(rendererLibPath);

        std::vector<std::pair<std::string, std::string>> renderers;
        std::vector<std::pair<std::string, std::string>> games;
        std::set<std::string> usedNames;

        for (const auto& entry : fs::directory_iterator("./lib/")) {
            if (entry.path().extension() != ".so")
                continue;

            auto meta = Arc::Core::extractLibraryMetadata(entry.path().string());
            if (!meta)
                continue;

            if (usedNames.count(meta->name)) {
                std::cerr << "Warning: duplicate library '" << meta->name << "' at '" 
                          << meta->path << "'. Skipping." << std::endl;
                continue;
            }

            usedNames.insert(meta->name);

            if (meta->type == Arc::LibraryType::Renderer) {
                renderers.emplace_back(meta->name, meta->path);
            } else if (meta->type == Arc::LibraryType::Game) {
                games.emplace_back(meta->name, meta->path);
            }
        }

        Arc::Core core(rendererLibPath, renderers, games);
        core.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
