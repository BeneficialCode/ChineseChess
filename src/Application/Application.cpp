#include "Application.h"
#include "Resources.h"
#include "Chess/Board.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



Application *Application::s_Instance = nullptr;

Application::Application(uint32_t width, uint32_t height, const std::string &name)
    : m_WindowProperties({width, height, name}), m_ChessViewportSize(width, height)
{
    if (!s_Instance)
    {
        s_Instance = this;
    }

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_Window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }
    // 通知GLFW将窗口的上下文设置为当前上下文
    glfwMakeContextCurrent(m_Window);

    glfwSwapInterval(1);

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
                               { Application::Get().OnWindowClose(); });

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int32_t width, int32_t height)
                              { Application::Get().OnWindowResize(width, height); });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
                       { Application::Get().OnKeyPressed(key, scancode, action, mods); });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int32_t button, int32_t action, int32_t mods)
                               { Application::Get().OnMouseButton(button, action, mods); });

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Run()
{
    m_Running = true;

    Init();

    while (m_Running)
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderImGui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);

        glfwPollEvents();
    }
}

glm::vec4 Application::HexToColour(uint32_t colour)
{
    static constexpr float normalise = 1.0f / 255.0f;
    uint8_t r = (colour & 0xff000000) >> 24;
    uint8_t g = (colour & 0x00ff0000) >> 16;
    uint8_t b = (colour & 0x0000ff00) >> 8;
    uint8_t a = (colour & 0x000000ff);
    return glm::vec4{r, g, b, a} * normalise;
}

void Application::Init()
{
    Renderer::Init(glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f), Resources::Shaders::VERTEX_SHADER, Resources::Shaders::FRAGMENT_SHADER);

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    if (!std::filesystem::exists("imgui.ini"))
        ImGui::LoadIniSettingsFromMemory(Resources::DEFAULT_IMGUI_INI);

    ImGui::StyleColorsDark();

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.GrabRounding = 4.0f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.WindowBorderSize = 0.0f;
    style.PopupBorderSize = 0.0f;
    style.ChildBorderSize = 0.0f;
    style.WindowMinSize = {200.0f, 200.0f};

    std::shared_ptr<Texture> chessPieces = std::make_shared<Texture>(Resources::Textures::CHESS_PIECES,
        sizeof(Resources::Textures::CHESS_PIECES));

    const float tileSize = (float)chessPieces->GetWidth() / 7.0f;
    for(int y=0;y<2;y++)
        for(int x=0;x<7;x++)
            m_ChessPieceSprites[y * 7 + x] = std::make_shared<SubTexture>(chessPieces, glm::vec2(x, y), glm::vec2(tileSize));

    m_DarkSquareColour = HexToColour(0x532A00FF);
    m_LightSquareColour = HexToColour(0xFFB160FF);

    m_BackgroundColour = {0.2f, 0.2f, 0.2f, 1.0f};


    m_BoardFEN = Board::StartFEN;
    m_BoardFEN.resize(100);

    FramebufferSpecification spec;
    spec.Width = m_WindowProperties.Width;
    spec.Height = m_WindowProperties.Height;
    m_ChessViewport = std::make_shared<Framebuffer>(spec);
}


void Application::RenderImGui()
{
    static bool s_ShowSettingsWindow = true, s_ShowFENWindow = true, s_ShowEngineWindow = true;

    {
        // Fullscreen stuff
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        // Submit the DockSpace
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::MenuItem("New");

                ImGui::Separator();

                if (ImGui::MenuItem("Quit"))
                    m_Running = false;

                ImGui::EndMenu();
            }
            else if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Colours")) { s_ShowSettingsWindow = true; }
                if (ImGui::MenuItem("FEN"))     { s_ShowFENWindow     = true; }
                if (ImGui::MenuItem("Engine"))  { s_ShowEngineWindow  = true; }

                ImGui::EndMenu();
            }
            else if (ImGui::BeginMenu("About")) {
                ImGui::Text("OpenGL Version: %s", Renderer::GetOpenGLVersion());

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    if (s_ShowFENWindow) {
        ImGui::Begin("FEN", &s_ShowFENWindow);

        if (ImGui::InputText("##FEN", m_BoardFEN.data(), m_BoardFEN.size(), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            
        }

        if (ImGui::Button("Copy FEN to clipboard"))
            glfwSetClipboardString(m_Window, m_BoardFEN.c_str());

        if (ImGui::Button("Reset board")) {
           
        }

        ImGui::End();
    }

    RenderChessPanel();
    RenderSettingsPanel(&s_ShowSettingsWindow);
    RenderAnalyzerPanel();
}

void Application::OnWindowClose()
{
    m_Running = false;
}

void Application::OnWindowResize(int32_t width, int32_t height)
{
    m_WindowProperties.Width = width;
    m_WindowProperties.Height = height;
}

void Application::OnKeyPressed(int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        m_Running = false;
    }
}

void Application::OnMouseButton(int32_t button, int32_t action, int32_t mods)
{

}

std::shared_ptr<SubTexture> Application::GetChessSprite(Piece piece) {
    switch (piece)
    {
    case BlackKing:
        return m_ChessPieceSprites[0];
    case BlackAdvisor:
        return m_ChessPieceSprites[1];
    case BlackBishop:
        return m_ChessPieceSprites[2];
    case BlackKnight:
        return m_ChessPieceSprites[3];
    case BlackRook:
        return m_ChessPieceSprites[4];
    case BlackCannon:
        return m_ChessPieceSprites[5];
    case BlackPawn:
        return m_ChessPieceSprites[6];
    case RedKing:
        return m_ChessPieceSprites[7];
    case RedAdvisor:
        return m_ChessPieceSprites[8];
    case RedBishop:
        return m_ChessPieceSprites[9];
    case RedKnight:
        return m_ChessPieceSprites[10];
    case RedRook:
        return m_ChessPieceSprites[11];
    case RedCannon:
        return m_ChessPieceSprites[12];
    case RedPawn:
        return m_ChessPieceSprites[13];
    case None:
        return nullptr;
    default:
        break;
    }

    throw std::runtime_error("Invalid piece");
}