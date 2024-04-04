#include "Application.h"

#include <iostream>

Application* Application::s_Instance = nullptr;

Application::Application(uint32_t width,uint32_t height,const std::string& name)
    : m_WindowProperties({width,height,name}) {
    if(!s_Instance){
        s_Instance = this;
    }

    
}

