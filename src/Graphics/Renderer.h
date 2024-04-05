#pragma once

#include <glm/glm.hpp>

class Renderer{
public:
    static void Init(const glm::mat4& projection,std::string_view vert,std::string_view frag);

    static const char* GetOpenGLVersion();

    Renderer() = delete;
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    ~Renderer();

    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    static const glm::mat4& GetProjectionMatrix();
    static void UpdateProjectionMatrix(const glm::mat4& projection);

    static void DrawRect(const glm::vec3& position, const glm::vec2& size, 
        const glm::vec4& colour);

    static void DrawRect(const glm::mat4& transform, const glm::vec4& colour);

    static void Flush();

    static void ClearScreen(glm::vec4 colour);
};