cmake_minimum_required(VERSION 3.24)
project(arcade)

set(
    SOURCE_FILES
    src/main.cpp
    src/Core/Core.cpp
    src/Game/Menu/Menu.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PUBLIC
    src/Core
    src/Renderer
    src/Game/Menu
    src/Include
)

####################### Ncurses ########################

find_package(Curses REQUIRED)

add_library(ncurses SHARED
    src/Renderer/Ncurses/Ncurses.cpp
)

set_target_properties(ncurses PROPERTIES
    PREFIX ""
    OUTPUT_NAME "arcade_ncurses"
)

target_include_directories(ncurses PUBLIC
    src/Renderer
    ${CURSES_INCLUDE_DIRS}
    src/Include
)

target_link_libraries(ncurses PRIVATE ${CURSES_LIBRARIES})

########################################################

######################### Sdl2 #########################

find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

add_library(sdl2 SHARED
    src/Renderer/Sdl2/Sdl2.cpp
)

set_target_properties(sdl2 PROPERTIES
    PREFIX ""
    OUTPUT_NAME "arcade_sdl2"
)

target_include_directories(sdl2 PUBLIC
    src/Renderer
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    src/Include
)

target_link_libraries(sdl2 ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

########################################################

######################### Sfml #########################

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

add_library(sfml SHARED
    src/Renderer/Sfml/Sfml.cpp
)

set_target_properties(sfml PROPERTIES
    PREFIX ""
    OUTPUT_NAME "arcade_sfml"
)

target_include_directories(sfml PUBLIC
    src/Renderer
    src/Include
)

target_link_libraries(sfml PRIVATE sfml-graphics sfml-window sfml-system)

########################################################

######################### Snake ########################

add_library(snake SHARED
    src/Game/Snake/Snake.cpp
)

set_target_properties(snake PROPERTIES
    PREFIX ""
    OUTPUT_NAME "arcade_snake"
)

target_include_directories(snake PUBLIC
    src/Renderer
    src/Game/Snake
    src/Core
    src/Include
    ${CURSES_INCLUDE_DIRS}
)

target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})

########################################################

###################### Minesweeper #####################

add_library(minesweeper SHARED
    src/Game/Minesweeper/Minesweeper.cpp
)

set_target_properties(minesweeper PROPERTIES
    PREFIX ""
    OUTPUT_NAME "arcade_minesweeper"
)

target_include_directories(minesweeper PUBLIC
    src/Renderer
    src/Game/Minesweeper
    src/Core
    src/Include
    ${CURSES_INCLUDE_DIRS}
)

target_link_libraries(minesweeper PRIVATE ${CURSES_LIBRARIES})


########################################################

################## Output Directories ##################


set(BIN_OUTPUT_DIR ${CMAKE_SOURCE_DIR})
set(LIBS_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib)

set_target_properties(${PROJECT_NAME} sdl2 ncurses sfml snake minesweeper PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIBS_OUTPUT_DIR}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
)

########################################################

################## Custom Targets ######################

add_custom_target(core
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(games
    DEPENDS snake minesweeper
)

add_custom_target(graphicals
    DEPENDS sdl2 sfml ncurses
)

########################################################
