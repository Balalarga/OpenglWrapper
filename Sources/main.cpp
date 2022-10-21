#include "Graphics/Rendering/Material.h"
#include "Graphics/Rendering/OpenglRender.h"
#include "Graphics/Rendering/Shader.h"
#include "Graphics/Rendering/ShaderPart.h"
#include "Graphics/Texture/TextureManager.h"
#include "System/SystemManager.h"
#include "System/WindowSystem/AppWindow.h"
#include "System/WindowSystem/WindowSystem.h"

using namespace std;

std::string vShaderCode = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;

uniform mat4 uModelMatrix = mat4(1);
uniform vec3 uCameraPos;

out vec4 vertColor;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
}
)";

std::string fShaderCode = R"(#version 330

in vec4 vertColor;
out vec4 fragColor;

uniform vec4 uColor;
uniform vec3 uCameraPos;

void main()
{
    fragColor = uColor;
}
)";


int main(int argc, char** argv)
{
    SystemManager& systemManager = SystemManager::Init();

    std::shared_ptr<Texture2d> texture = TextureManager::Instance().LoadTexture("newTexture", "../Assets/Gear.png");
    if (!texture)
        return -1;
    
    OpenglRender& render = systemManager.windowSystem->CreateRender<OpenglRender>(systemManager.windowSystem->GetWindow().GetInnerWindow());

    auto vPart = std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, vShaderCode);
    auto fPart = std::make_shared<ShaderPart>(ShaderPart::Type::Fragment, fShaderCode);
    auto shader = std::make_shared<Shader>(vPart, fPart);
    shader->Compile(true);
    
    Material mat(shader);
    mat.AddUniform("uColor");
    
    AppWindow& window = systemManager.windowSystem->GetWindow();
    window.Show();
    
    SystemManager::Destroy();
    return 0;
}
