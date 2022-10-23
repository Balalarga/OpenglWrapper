#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics/Shading//Material.h"
#include "Graphics/Rendering/OpenglRender.h"
#include "Graphics/Shading/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "System/SystemManager.h"
#include "System/WindowSystem/AppWindow.h"
#include "System/WindowSystem/WindowSystem.h"

using namespace std;

std::string vShaderCode = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec4 iVertColor;
layout(location = 2)in vec2 iVertUv;

uniform mat4 uModelMatrix = mat4(1);
uniform vec3 uCameraPos;

out vec4 vertColor;
out vec2 vertUv;

void main()
{
    gl_Position = uModelMatrix * vec4(iVert, 1.0);
    vertColor = iVertColor;
}
)";

std::string fShaderCode = R"(#version 330

in vec2 vertUv;
in vec4 vertColor;
out vec4 fragColor;

uniform vec4 uColor;
uniform vec3 uCameraPos;
uniform sampler2D uTexture;

void main()
{
    fragColor = texture(uTexture, vertUv);
}
)";


int main(int argc, char** argv)
{
    SystemManager& systemManager = SystemManager::Init();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    OpenglRender& render = systemManager.windowSystem->CreateRender<OpenglRender>(systemManager.windowSystem->GetWindow().GetInnerWindow());
    
    std::shared_ptr<Texture2d> texture = TextureManager::Instance().LoadTexture("newTexture", "../Assets/Gear.png");
    if (!texture)
        return -1;

    std::shared_ptr<ShaderPart> vPart = ShaderManager::LoadPart("def", ShaderPart::Type::Vertex, vShaderCode);
    std::shared_ptr<ShaderPart> fPart = ShaderManager::LoadPart("def", ShaderPart::Type::Fragment, fShaderCode);
    std::shared_ptr<Shader> shader = ShaderManager::CreateFrom("def", vPart, fPart);
    ShaderManager::CompileAll();

    struct {
        glm::vec3 pos;
        glm::vec4 color;
        glm::vec2 uv;
    } triangle[] {
        {{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, {-1.0f, -1.0f}},
        {{-0.5f,  0.5f, 0.f}, {1.f, 1.f, 0.f, 1.f}, {-1.0f,  1.0f}},
        {{ 0.5f,  0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 1.0f,  1.0f}},
        
        {{ 0.5f,  0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 1.0f,  1.0f}},
        {{ 0.5f, -0.5f, 0.f}, {1.f, 1.f, 0.f, 1.f}, { 1.0f, -1.0f}},
        {{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, {-1.0f, -1.0f}},
    };
    Material mat(shader);
    mat.AddUniform("uColor");
    mat.AddUniform("uTexture");
    
    Buffer buffer(DataPtr(triangle, sizeof(triangle)/sizeof(triangle[0]), sizeof(triangle[0])), BufferLayout().Float(3).Float(4).Float(2));
    
    render.CreateObject<Object>(buffer, mat, texture.get());
    
    AppWindow& window = systemManager.windowSystem->GetWindow();
    window.Show();
    
    SystemManager::Destroy();
    return 0;
}
;