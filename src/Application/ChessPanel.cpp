#include "Application.h"

#include "Graphics/Renderer.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

void Application::RenderBoardLines()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // 设置线条颜色为黑色
    glColor3f(0.0f, 0.0f, 0.0f);

    float width = 1.0f;
    // 绘制横线
    for (int i = 0; i < 10; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(-4.0f, 5.0f - i * width);
        glVertex2f(4.0f, 5.0f - i * width);
        glEnd();
    }

    glBegin(GL_LINES);
    glVertex2f(-4.0f, 5.0f);
    glVertex2f(-4.0f, -4.0f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(4.0f, 5.0f);
    glVertex2f(4.0f, -4.0f);
    glEnd();

    // 绘制上竖线
    for (int i = 1; i < 8; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(-4.0f + i * width, 5.0f);
        glVertex2f(-4.0f + i * width, 5.0f - 4 * width);
        glEnd();
    }

    // 绘制下竖线
    for (int i = 1; i < 8; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(-4.0f + i * width, 0.0f);
        glVertex2f(-4.0f + i * width, 0.0f - 4 * width);
        glEnd();
    }

    // 上部九宫格第一条斜线
    glBegin(GL_LINES);
    glVertex2f(-4.0f + 3 * width, 5.0f);
    glVertex2f(-4.0f + 5 * width, 5.0f - 2 * width);
    glEnd();

    // 上部九宫格第二条斜线
    glBegin(GL_LINES);
    glVertex2f(-4.0f + 5 * width, 5.0f);
    glVertex2f(-4.0f + 3 * width, 5.0f - 2 * width);
    glEnd();

    // 下部九宫格第一条斜线
    glBegin(GL_LINES);
    glVertex2f(-4.0f + 3 * width, -2.0f);
    glVertex2f(-4.0f + 5 * width, -2.0f - 2 * width);
    glEnd();

    // 下部九宫格第二条斜线
    glBegin(GL_LINES);
    glVertex2f(-4.0f + 5 * width, -2.0f);
    glVertex2f(-4.0f + 3 * width, -2.0f - 2 * width);
    glEnd();

    float shortLineWidth = 0.2f;
    // 绘制-3位置炮位
    glBegin(GL_LINES);
    glVertex2f(-3.0f - 2 * shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(-3.0f - shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(-3.0f - shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(-3.0f - shortLineWidth, 3.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3.0f - 2 * shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(-3.0f - shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(-3.0f - shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(-3.0f - shortLineWidth, -2.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3.0f + 2 * shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(-3.0f + shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(-3.0f + shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(-3.0f + shortLineWidth, 3.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3.0f + 2 * shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(-3.0f + shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(-3.0f + shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(-3.0f + shortLineWidth, -2.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3 - 2 * shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(-3 - shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(-3 - shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(-3 - shortLineWidth, 3.0f - shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3 - 2 * shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(-3 - shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(-3 - shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(-3 - shortLineWidth, -2.0f - shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3 + 2 * shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(-3 + shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(-3 + shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(-3 + shortLineWidth, 3.0f - shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3 + 2 * shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(-3 + shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(-3 + shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(-3 + shortLineWidth, -2.0f - shortLineWidth * 2);
    glEnd();

    // 绘制3位置炮位
    glBegin(GL_LINES);
    glVertex2f(3.0f - 2 * shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(3.0f - shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(3.0f - shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(3.0f - shortLineWidth, 3.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3.0f - 2 * shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(3.0f - shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(3.0f - shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(3.0f - shortLineWidth, -2.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3.0f + 2 * shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(3.0f + shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(3.0f + shortLineWidth, 3.0f + shortLineWidth);
    glVertex2f(3.0f + shortLineWidth, 3.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3.0f + 2 * shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(3.0f + shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(3.0f + shortLineWidth, -2.0f + shortLineWidth);
    glVertex2f(3.0f + shortLineWidth, -2.0f + shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3 - 2 * shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(3 - shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(3 - shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(3 - shortLineWidth, 3.0f - shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3 - 2 * shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(3 - shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(3 - shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(3 - shortLineWidth, -2.0f - shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3 + 2 * shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(3 + shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(3 + shortLineWidth, 3.0f - shortLineWidth);
    glVertex2f(3 + shortLineWidth, 3.0f - shortLineWidth * 2);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3 + 2 * shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(3 + shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(3 + shortLineWidth, -2.0f - shortLineWidth);
    glVertex2f(3 + shortLineWidth, -2.0f - shortLineWidth * 2);
    glEnd();

    // 绘制兵位置

    /// 2附近的兵位置
    glBegin(GL_LINES);
    glVertex2f(-3.8f, 2.4f);
    glVertex2f(-3.8f, 2.2f);
    glVertex2f(-3.8f, 2.2f);
    glVertex2f(-3.6f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.8f, 2.4f);
    glVertex2f(-1.8f, 2.2f);
    glVertex2f(-1.8f, 2.2f);
    glVertex2f(-1.6f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.2f, 2.4f);
    glVertex2f(0.2f, 2.2f);
    glVertex2f(0.2f, 2.2f);
    glVertex2f(0.4f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(2.2f, 2.4f);
    glVertex2f(2.2f, 2.2f);
    glVertex2f(2.2f, 2.2f);
    glVertex2f(2.4f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-3.8f, 1.6f);
    glVertex2f(-3.8f, 1.8f);
    glVertex2d(-3.8f, 1.8f);
    glVertex2f(-3.6f, 1.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.8f, 1.6f);
    glVertex2f(-1.8f, 1.8f);
    glVertex2d(-1.8f, 1.8f);
    glVertex2f(-1.6f, 1.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.2f, 1.6f);
    glVertex2f(0.2f, 1.8f);
    glVertex2d(0.2f, 1.8f);
    glVertex2f(0.4f, 1.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(2.2f, 1.6f);
    glVertex2f(2.2f, 1.8f);
    glVertex2d(2.2f, 1.8f);
    glVertex2f(2.4f, 1.8f);
    glEnd();

    /// y为-1附近的兵位置
    glBegin(GL_LINES);
    glVertex2f(-3.8f, -0.6f);
    glVertex2f(-3.8f, -0.8f);
    glVertex2f(-3.8f, -0.8f);
    glVertex2f(-3.6f, -0.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-1.8f, -0.6f);
    glVertex2f(-1.8f, -0.8f);
    glVertex2f(-1.8f, -0.8f);
    glVertex2f(-1.6f, -0.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.2f, -0.8f);
    glVertex2f(0.2f, -0.8f);
    glVertex2f(0.4f, -0.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(2.2f, -0.6f);
    glVertex2f(2.2f, -0.8f);
    glVertex2f(2.2f, -0.8f);
    glVertex2f(2.4f, -0.8f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-3.8f, -1.4f);
    glVertex2d(-3.8f, -1.2f);
    glVertex2d(-3.8f, -1.2f);
    glVertex2d(-3.6f, -1.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-1.8f, -1.4f);
    glVertex2d(-1.8f, -1.2f);
    glVertex2d(-1.8f, -1.2f);
    glVertex2d(-1.6f, -1.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(0.2f, -1.4f);
    glVertex2d(0.2f, -1.2f);
    glVertex2d(0.2f, -1.2f);
    glVertex2d(0.4f, -1.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(2.2f, -1.4f);
    glVertex2d(2.2f, -1.2f);
    glVertex2d(2.2f, -1.2f);
    glVertex2d(2.4f, -1.2f);
    glEnd();

    // 绘制最右侧兵位
    glBegin(GL_LINES);
    glVertex2d(3.8f, 2.4f);
    glVertex2d(3.8f, 2.2f);
    glVertex2d(3.8f, 2.2f);
    glVertex2d(3.6f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(1.8f, 2.4f);
    glVertex2d(1.8f, 2.2f);
    glVertex2d(1.8f, 2.2f);
    glVertex2d(1.6f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-0.2f, 2.4f);
    glVertex2d(-0.2f, 2.2f);
    glVertex2d(-0.2f, 2.2f);
    glVertex2d(-0.4f, 2.2f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(3.6f, 1.8f);
    glVertex2d(3.8f, 1.8f);
    glVertex2d(3.8f, 1.8f);
    glVertex2d(3.8f, 1.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(1.6f, 1.8f);
    glVertex2d(1.8f, 1.8f);
    glVertex2d(1.8f, 1.8f);
    glVertex2d(1.8f, 1.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-0.4f, 1.8f);
    glVertex2d(-0.2f, 1.8f);
    glVertex2d(-0.2f, 1.8f);
    glVertex2d(-0.2f, 1.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(-2.4f, 1.8f);
    glVertex2d(-2.2f, 1.8f);
    glVertex2d(-2.2f, 1.8f);
    glVertex2d(-2.2f, 1.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-2.4f, 2.2f);
    glVertex2f(-2.2f, 2.2f);
    glVertex2f(-2.2f, 2.2f);
    glVertex2f(-2.2f, 2.4f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-2.4f, -0.8f);
    glVertex2f(-2.2f, -0.8f);
    glVertex2f(-2.2f, -0.8f);
    glVertex2f(-2.2f, -0.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.4f, -0.8f);
    glVertex2f(-0.2f, -0.8f);
    glVertex2f(-0.2f, -0.8f);
    glVertex2f(-0.2f, -0.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.6f, -0.8f);
    glVertex2f(1.8f, -0.8f);
    glVertex2f(1.8f, -0.8f);
    glVertex2f(1.8f, -0.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3.6f, -0.8f);
    glVertex2f(3.8f, -0.8f);
    glVertex2f(3.8f, -0.8f);
    glVertex2f(3.8f, -0.6f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-2.4f, -1.2f);
    glVertex2f(-2.2f, -1.2f);
    glVertex2f(-2.2f, -1.2f);
    glVertex2f(-2.2f, -1.4f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.4f, -1.2f);
    glVertex2f(-0.2f, -1.2f);
    glVertex2f(-0.2f, -1.2f);
    glVertex2f(-0.2f, -1.4f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(1.6f, -1.2f);
    glVertex2f(1.8f, -1.2f);
    glVertex2f(1.8f, -1.2f);
    glVertex2f(1.8f, -1.4f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(3.6f, -1.2f);
    glVertex2f(3.8f, -1.2f);
    glVertex2f(3.8f, -1.2f);
    glVertex2f(3.8f, -1.4f);
    glEnd();
}

void Application::RenderBoard()
{
    Renderer::ClearScreen({0.0f, 0.0f, 0.0f, 1.0f});

    // Resize framebuffer according to viewport size
    FramebufferSpecification spec = m_ChessViewport->GetSpecification();
    if ((float)spec.Width != m_ChessViewportSize.x || (float)spec.Height != m_ChessViewportSize.y)
    {
        m_ChessViewport->Resize((uint32_t)m_ChessViewportSize.x, (uint32_t)m_ChessViewportSize.y);

        // I don't know what to call this variable
        constexpr float temp = 5.6f;

        float aspectRatio = m_ChessViewportSize.x / m_ChessViewportSize.y;

        // Resize the coordinates so the chessboard size
        // is the minimumm of the width and the height
        if (aspectRatio <= 1.0f)
            Renderer::UpdateProjectionMatrix(glm::ortho(-temp, temp, -temp / aspectRatio, temp / aspectRatio));
        else
            Renderer::UpdateProjectionMatrix(glm::ortho(-temp * aspectRatio, temp * aspectRatio, -temp, temp));

        // Transform the ImGui mouse coordinates to OpenGL coordinates
        m_CoordinateTransform = glm::inverse(Renderer::GetProjectionMatrix());
        m_CoordinateTransform = glm::scale(m_CoordinateTransform, {1 / (m_ChessViewportSize.x * 0.5f), 1 / (m_ChessViewportSize.y * -0.5f), 1.0f});
        m_CoordinateTransform = glm::translate(m_CoordinateTransform, {m_ChessViewportSize.x * -0.5f, m_ChessViewportSize.y * -0.5f, 0.0f});
    }

    // Render chessboard to framebuffer
    m_ChessViewport->Bind();
    Renderer::ClearScreen(m_BackgroundColour);

    // Draw board lines
    RenderBoardLines();

    // Draw pieces
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 9; x++) {
            Square idx = 51 + x + y* 16;
            std::shared_ptr<SubTexture> piece = GetChessSprite(m_Board[idx]);
            if(piece && m_SelectedPiece != idx)
            {
                Renderer::DrawRect({-4.0f + x, 5.0f - y,0.0f}, {1.0f, 1.0f}, piece);
            }
        }
    }

    // Draw selected piece
    if(m_SelectedPiece != INVALID_SQUARE)
        Renderer::DrawRect({m_BoardMousePosition.x,m_BoardMousePosition.y,0.5f}, {1.0f, 1.0f}, GetChessSprite(m_Board[m_SelectedPiece]));

    Renderer::Flush();

    // Deselect framebuffer to render ImGui to window
    m_ChessViewport->Unbind();
}

void Application::RenderChessPanel()
{
    RenderBoard();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, {400.f, 500.f}); // For when window is floating

    ImGui::Begin("Chessboard");

    // Get the position of the viewport relative to the panel position
    // (The tab bar pushes it down)
    auto [offsetX, offsetY] = ImGui::GetCursorPos();

    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    m_ChessViewportSize = {viewportSize.x, viewportSize.y};

    ImTextureID texture = (void *)(intptr_t)m_ChessViewport->GetColourAttachment();
    int framePadding = 0;
    ImVec4 backgroundColour = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 tintColour = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    // Using ImageButton instead of Image allows the viewport to
    // not be dragged when it is floating when dragging the pieces
    ImGui::ImageButton(texture, viewportSize, {0, 1}, {1, 0}, framePadding, backgroundColour, tintColour);

    // Get mouse position on the board
    auto [mouseX, mouseY] = ImGui::GetMousePos();    // Absolute mouse position
    auto [windowX, windowY] = ImGui::GetWindowPos(); // Top-Left corner of window

    glm::vec2 mousePosition = {mouseX, mouseY};
    glm::vec2 viewportPosition = {windowX + offsetX, windowY + offsetY};
    glm::vec2 relativeMousePos = mousePosition - viewportPosition;

    m_BoardMousePosition = m_CoordinateTransform * glm::vec4{relativeMousePos.x, relativeMousePos.y, 1.0f, 1.0f};

    ImGui::End();

    ImGui::PopStyleVar(2);
}