cmake_minimum_required(VERSION 3.5)

project(ChineseChess)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCES
    "src/Application/Main.cpp"
    "src/Application/Application.cpp"
    "src/Application/Application.h"
    "src/Application/Resources.h"
    "src/Application/ChessPanel.cpp"
    "src/Application/SettingsPanel.cpp"
    "src/Application/AnalyzerPanel.cpp"

    "src/Graphics/Framebuffer.h"
    "src/Graphics/Framebuffer.cpp"
    "src/Graphics/Renderer.h"
    "src/Graphics/Renderer.cpp"
    "src/Graphics/Buffer.h"
    "src/Graphics/Buffer.cpp"
    "src/Graphics/VertexArray.h"
    "src/Graphics/VertexArray.cpp"
    "src/Graphics/Shader.h"
    "src/Graphics/Shader.cpp"
    "src/Graphics/Texture.h"
    "src/Graphics/Texture.cpp"
    "src/Graphics/SubTexture.h"
    "src/Graphics/SubTexture.cpp"

    "src/Chess/Board.h"
    "src/Chess/Board.cpp"
    "src/Chess/Move.h"

    "dependencies/imgui/imgui.cpp"
    "dependencies/imgui/imgui_demo.cpp"
    "dependencies/imgui/imgui_draw.cpp"
    "dependencies/imgui/imgui_tables.cpp"
    "dependencies/imgui/imgui_widgets.cpp"
    "dependencies/imgui/backends/imgui_impl_glfw.cpp"
    "dependencies/imgui/backends/imgui_impl_opengl3.cpp"
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(${PROJECT_NAME} PRIVATE
    "src"
)

# ------------------- DEPENDENCIES -------------------
set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(dependencies/glfw)

# OpenGL
find_package(OpenGL REQUIRED)

# glad
add_subdirectory(dependencies/glad)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    ${OPENGL_LIBRARY}
    glad    
)

set_target_properties(glfw update_mappings glad PROPERTIES FOLDER "DEPENDENCIES/")

target_include_directories(${PROJECT_NAME} PRIVATE
    "dependencies/stb_image"
    "dependencies/glm/"
    "dependencies/imgui"
)