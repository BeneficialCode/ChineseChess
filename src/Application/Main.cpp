#include "Application.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


#include <Windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    LPSTR lpCmdLine, int nCmdShow)
{
    // get the screen width and height
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    screenWidth = 1600;
    screenHeight = 960;

    auto app = new Application(screenWidth, screenHeight, "Chinese Chess");
    try{
        app->Run();
    }catch(const std::exception& e){
        MessageBox(glfwGetWin32Window(app->GetWindow()),e.what(),"Error",MB_OK | MB_ICONERROR);
    }

    delete app;

    return 0;
}