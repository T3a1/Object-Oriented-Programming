/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** DLloader
*/

#pragma once

    #include <dlfcn.h>
    #include <iostream>
    #include <string>
    #include <map>

namespace Arc
{
    struct Item;
    
    /**
     * @class DLloader
     * @brief Template class for loading dynamic libraries at runtime.
     * 
     * Handles opening shared libraries (.so files) and retrieving the
     * entryPoint function to create instances of game or renderer implementations.
     * 
     * @tparam T The interface type to instantiate (IGame or IRenderer)
     */
    template <typename T>
    class DLloader
    {
        private:
            void *_handle;
            T *(*_entryPoint)(std::map<std::string, Item>&);

        public:
            /**
             * @brief Loads a dynamic library and resolves the entryPoint symbol.
             * @param libPath Path to the shared library file
             */
            DLloader(const std::string &libPath) : _handle(nullptr), _entryPoint(nullptr)
            {
                _handle = dlopen(libPath.c_str(), RTLD_LAZY);
                if (!_handle) {
                    std::cerr << "[ERROR DLloader] Failed to dlopen: " << dlerror() << std::endl;
                    return;
                }
                
                dlerror();
                _entryPoint = reinterpret_cast<T *(*)(std::map<std::string, Item>&)>(dlsym(_handle, "entryPoint"));
                if (dlerror()) {
                    std::cerr << "[ERROR DLloader] Could not find entryPoint" << std::endl;
                    _entryPoint = nullptr;
                }
            }

            /**
             * @brief Destructor - does not unload the library.
             * 
             * Libraries remain loaded for the application lifetime to keep
             * instances valid.
             */
            ~DLloader()
            {
            }

            /**
             * @brief Creates an instance using the loaded library's entryPoint.
             * @param itemList Item map to pass to the entryPoint
             * @return Pointer to the created instance, or nullptr if loading failed
             */
            T *getInstance(std::map<std::string, Item>& itemList)
            {
                if (!_entryPoint) {
                    std::cerr << "[ERROR DLloader::getInstance] entryPoint is null" << std::endl;
                    return nullptr;
                }
                T* instance = _entryPoint(itemList);
                return instance;
            }
    };
}
