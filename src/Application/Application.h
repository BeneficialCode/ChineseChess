#pragma once

#include <array>
#include <string>

#include "Graphics/Framebuffer.h"
#include "Graphics/SubTexture.h"

#include "Chess/Board.h"

#include <glm/glm.hpp>

struct GLFWwindow;

class Application {
public:
    Application(uint32_t width,uint32_t height,const std::string& name);
    Application(const Application&) = delete;
    Application(Application&&) = delete;

    ~Application();

    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    static Application& Get() { return *s_Instance; }

    GLFWwindow* GetWindow() const { return m_Window; }

    void Run();

    glm::vec4 HexToColour(uint32_t colour);

private:
    void Init();
    void RenderBoard();
    void RenderImGui();
    void RenderChessPanel();
    void RenderAnalyzerPanel();
    void RenderSettingsPanel(bool* show);
    void RenderBoardLines();

    std::shared_ptr<SubTexture> GetChessSprite(Piece piece);

    void OnWindowClose();
    void OnWindowResize(int32_t width,int32_t height);
    void OnKeyPressed(int32_t key,int32_t scancode,int32_t action,int32_t mods);
    void OnMouseButton(int32_t button,int32_t action,int32_t mods);

private:
    static Application* s_Instance;

    GLFWwindow* m_Window = nullptr;

    struct {
        uint32_t Width,Height;
        std::string Title;
    }m_WindowProperties;

    bool m_Running = false;
    
    Board m_Board;
    Square m_SelectedPiece = INVALID_SQUARE;
    bool m_IsHoldingPiece = false;
    std::vector<Move> m_LegalMoves;
    std::string m_BoardFEN;

    std::array<std::shared_ptr<SubTexture>,14> m_ChessPieceSprites;

    std::shared_ptr<Framebuffer> m_ChessViewport;
    glm::vec2 m_ChessViewportSize;
    glm::vec2 m_BoardMousePosition;
    glm::mat4 m_CoordinateTransform;

    glm::vec4 m_LightSquareColour;
    glm::vec4 m_DarkSquareColour;
    glm::vec4 m_LegalMoveColour;
    
    glm::vec4 m_BackgroundColour;


    
    
};