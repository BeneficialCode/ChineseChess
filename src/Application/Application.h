#pragma once

#include <array>
#include <string>

class Application {
public:
    Application(uint32_t width,uint32_t height,const std::string& name);
    Application(const Application&) = delete;
    Application(Application&&) = delete;

    ~Application();

    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    static Application& Get() { return *s_Instance; }

    void Run();

private:
    void Init();
    void RenderBoard();
    void RenderImGui();
    void RenderChessPanel();
    
    void OnWindowClose();
    void OnWindowResize(uint32_t width,int32_t height);
    void OnKeyPressed(int32_t key,int32_t scancode,int32_t action,int32_t mods);
    void OnMouseButton(int32_t button,int32_t action,int32_t mods);

private:
    static Application* s_Instance;

    struct {
        uint32_t Width,Height;
        std::string Title;
    }m_WindowProperties;

    bool m_Running = false;

    std::string m_BoardFEN;

    

};