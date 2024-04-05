#include "Buffer.h"
#include "Renderer.h"

#include <algorithm>
#include <array>
#include <memory>

#include "Shader.h"
#include "VertexArray.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

namespace {
    constexpr size_t maxQuadCount = 100;
    constexpr size_t maxVertexCount = maxQuadCount * 4;
    constexpr size_t maxIndexCount = maxQuadCount * 6;

    constexpr int32_t maxTextureCount = 32;

    struct Vertex{
        glm::vec4 Position;
        glm::vec2 Colour;
        glm::vec2 TexCoord;
        float TextureSlot;
    };

    constexpr std::initializer_list<VertexAttribute> s_VertexLayout = {
        {VertexAttribute::Type::Float, 4}, // Position
        {VertexAttribute::Type::Float, 2}, // Colour
        {VertexAttribute::Type::Float, 2}, // Texture Coordinate
        {VertexAttribute::Type::Float, 1}  // Texture ID
    };

    std::unique_ptr<IndexBuffer> s_IndexBuffer;
    std::unique_ptr<Shader> s_Shader;
    std::unique_ptr<VertexBuffer> s_VertexBuffer;
    std::unique_ptr<VertexArray> s_VertexArray;

    Vertex* s_Vertecies = nullptr;
    Vertex* s_NextVertex = nullptr;
    uint32_t* s_Indicies = nullptr;
    uint32_t* s_NextIndex = nullptr;

    // Slot of next texture. Begins at 1 because 0 is reserved for no texture
    uint32_t m_NextTextureSlot = 1;

    constexpr std::array<glm::vec4, 4> s_RectPositions = {
        glm::vec4{ -0.5f, -0.5f, 0.0f, 1.0f },
        glm::vec4{  0.5f, -0.5f, 0.0f, 1.0f },
        glm::vec4{  0.5f,  0.5f, 0.0f, 1.0f },
        glm::vec4{ -0.5f,  0.5f, 0.0f, 1.0f },
    };

    constexpr std::array<uint32_t, 12> s_RectIndicies = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,
    };

    constexpr std::array<glm::vec2, 4> s_TextureCoords = {
        glm::vec2{ 0.0f, 0.0f },
        glm::vec2{ 1.0f, 0.0f },
        glm::vec2{ 1.0f, 1.0f },
        glm::vec2{ 0.0f, 1.0f },
    };

    glm::mat4 s_ProjectionMatrix(1.0f);
}

void Renderer::Init(const glm::mat4& projection, std::string_view vert, std::string_view frag) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    s_IndexBuffer = std::make_unique<IndexBuffer>(maxIndexCount * sizeof(uint32_t));
    s_Shader = std::make_unique<Shader>(vert.data(), frag.data());
    s_VertexBuffer = std::make_unique<VertexBuffer>(maxVertexCount * sizeof(Vertex));
    s_VertexArray = std::make_unique<VertexArray>(*s_VertexBuffer, s_VertexLayout);

    s_Vertecies = new Vertex[maxVertexCount];
    s_Indicies = new uint32_t[maxIndexCount];

    s_NextVertex = s_Vertecies;
    s_NextIndex = s_Indicies;

    UpdateProjectionMatrix(projection);
}

const char* Renderer::GetOpenGLVersion() {
    return (const char*)glGetString(GL_VERSION);
}

Renderer::~Renderer() {
    delete[] s_Vertecies;
    delete[] s_Indicies;
}

const glm::mat4& Renderer::GetProjectionMatrix() {
    return s_ProjectionMatrix;
}

void Renderer::UpdateProjectionMatrix(const glm::mat4& projection) {
    s_ProjectionMatrix = projection;
    glm::mat4 viewMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0));
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0));

    s_Shader->SetUniform("u_MVP", projection * viewMatrix * modelMatrix);
}

void Renderer::DrawRect(const glm::vec3& position, const glm::vec2& size, 
        const glm::vec4& colour){
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    DrawRect(transform, colour);
}

void Renderer::DrawRect(const glm::mat4& transform, const glm::vec4& colour){
    uint64_t vertexCount = s_NextVertex - s_Vertecies;

    if (vertexCount > maxVertexCount - 4) {
        Flush();
        vertexCount = s_NextVertex - s_Vertecies;
    }

    for (size_t i = 0; i < 4; i++) {
        s_NextVertex->Position = transform * s_RectPositions[i];
        s_NextVertex->Colour = colour;
        s_NextVertex->TexCoord = { 0.0f, 0.0f };
        s_NextVertex->TextureSlot = 0.0f;  // slot 0 corresponds to no texture
        s_NextVertex++;
    }

    for (size_t i = 0; i < 6; i++) {
        *s_NextIndex = (uint32_t)vertexCount + s_RectIndicies[i];
        s_NextIndex++;
    }
}

void Renderer::Flush(){
    s_VertexArray->Bind();
    s_IndexBuffer->Bind();
    s_Shader->Bind();

    uint64_t vertexCount = s_NextVertex - s_Vertecies;
    uint64_t indexCount = s_NextIndex - s_Indicies;
    
    s_VertexBuffer->SetData(s_Vertecies, vertexCount * sizeof(Vertex));
    s_IndexBuffer->SetData(s_Indicies, (uint32_t)indexCount);

    glDrawElements(GL_TRIANGLES, (int32_t)indexCount, GL_UNSIGNED_INT, nullptr);

    s_NextVertex = s_Vertecies;
    s_NextIndex = s_Indicies;
    
}

void Renderer::ClearScreen(glm::vec4 colour){
    glClearColor(colour.r, colour.g, colour.b, colour.a);
    glClear(GL_COLOR_BUFFER_BIT);
}