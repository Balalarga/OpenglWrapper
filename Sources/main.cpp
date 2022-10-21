#include "Graphics/Rendering/OpenglRender.h"
#include "System/SystemManager.h"
#include "System/WindowSystem/AppWindow.h"
#include "System/WindowSystem/WindowSystem.h"

using namespace std;

std::string vShaderCode = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;

out vec4 vertColor;

void main()
{
    gl_Position = vec4(iVert, 1.0);
    vertColor = iVertColor;
}
)";


std::string fShaderCode = R"(#version 330

in vec4 vertColor;
out vec4 fragColor;

void main()
{
    fragColor = vertColor;
}
)";


int main(int argc, char** argv)
{
    SystemManager& systemManager = SystemManager::Init();

    // std::shared_ptr<Texture2d> texture = TextureManager::Instance().LoadTexture("newTexture", "../Assets/Gear.png"); 
    // if (!texture)
        // return -1;
    
    OpenglRender& render = systemManager.windowSystem->CreateRender<OpenglRender>(systemManager.windowSystem->GetWindow().GetInnerWindow());
    
    AppWindow& window = systemManager.windowSystem->GetWindow();
    window.Show();
    
    SystemManager::Destroy();
    return 0;
}
