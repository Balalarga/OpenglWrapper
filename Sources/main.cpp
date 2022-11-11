#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Application.h"
#include "Graphics/Materials/BaseMaterial.h"
#include "Graphics/Materials/Texture2dMaterial.h"
#include "Graphics/Rendering/OpenglRender.h"
#include "Graphics/Texture/TextureManager.h"
#include "System/SystemManager.h"
#include "System/WindowSystem/AppWindow.h"
#include "System/WindowSystem/WindowSystem.h"
#include "Utils/ShaderLoader.h"

using namespace std;
using namespace Oglw;

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
    vertUv = iVertUv;
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

class MyApp: public Application
{
public:
    std::shared_ptr<Texture2dMaterial> baseMat;
    
    void Init() override
    {
        WindowSystem* windowSystem = GetSystemManager().windowSystem;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        OpenglRender& render = windowSystem->CreateRender<OpenglRender>(windowSystem->GetWindow().GetInnerWindow());

        const std::shared_ptr<Texture2d> texture = TextureManager::Instance().LoadTexture("newTexture", ASSETS_DIR"/Image.png");
        if (!texture)
            return;
    
        const std::shared_ptr<Shader> shader = ShaderLoader::LoadCode(vShaderCode, fShaderCode);
        shader->Compile();

        Texture2dMaterial::VertexData triangle[]
        {
            {{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 0.0f,  0.0f}},
            {{-0.5f,  0.5f, 0.f}, {1.f, 1.f, 0.f, 1.f}, { 0.0f,  1.0f}},
            {{ 0.5f,  0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 1.0f,  1.0f}},
            {{ 0.5f,  0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 1.0f,  1.0f}},
            {{ 0.5f, -0.5f, 0.f}, {1.f, 1.f, 0.f, 1.f}, { 1.0f,  0.0f}},
            {{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 0.0f,  0.0f}},
        };
        baseMat = std::make_shared<Texture2dMaterial>(shader, texture.get());
        baseMat->SetColor({1, 0, 0, 1});
        Buffer buffer = baseMat->CreateBufferWithLayout(DataPtr(triangle, std::size(triangle), sizeof(Texture2dMaterial::VertexData)));
        render.CreateObject<Object>(buffer, baseMat.get());
    }
    
    void Destroy() override
    {
        
    }
};

int main(int argc, char** argv)
{
    MyApp app;
    
    app.Run();
    
    return 0;
}