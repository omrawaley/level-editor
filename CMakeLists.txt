cmake_minimum_required(VERSION 3.4)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)

project(level_editor)

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED COMPONENTS SDL2_image)

set(SRC_DIR src)
set(IMGUI_DIR deps/imgui)
set(IMGUI_BACKENDS_DIR deps/imgui/backends)
add_executable(editor ${SRC_DIR}/main.cpp ${SRC_DIR}/editor.cpp ${SRC_DIR}/level.cpp ${SRC_DIR}/codeGenerator.cpp ${SRC_DIR}/gui.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_BACKENDS_DIR}/imgui_impl_sdl2.cpp ${IMGUI_BACKENDS_DIR}/imgui_impl_sdlrenderer2.cpp)

target_link_libraries(editor PRIVATE SDL2::SDL2)
target_link_libraries(editor PRIVATE SDL2_image::SDL2_image)
