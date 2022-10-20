#include <iostream>
#include <SDL_syswm.h>

#include "OpenGL/Core/Geometry.h"
#include "OpenGL/Core/Object.h"
#include "OpenGL/Core/Scene.h"
#include "OpenGL/Core/Texture2d.h"

#include "WindowSystem/OpenglWindow.h"

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

std::string vTextureShaderCode = R"(#version 330

layout(location = 0)in vec3 iVert;
layout(location = 1)in vec2 iUv;

out vec2 vUv;

void main()
{
    gl_Position = vec4(iVert, 1.0);
    vUv = iUv;
}
)";
std::string fTextureShaderCode = R"(#version 330

in vec2 vUv;

out vec4 fragColor;

uniform sampler2D uTexture;

void main()
{
    fragColor = texture(uTexture, vUv);
}
)";

ShaderPart vShader(ShaderPart::Type::Vertex, vShaderCode);
ShaderPart fShader(ShaderPart::Type::Fragment, fShaderCode);
Shader shader(&vShader, &fShader);

ShaderPart vTexturedShader(ShaderPart::Type::Vertex, vTextureShaderCode);
ShaderPart fTexturedShader(ShaderPart::Type::Fragment, fTextureShaderCode);
Shader texturedShader(&vTexturedShader, &fTexturedShader);

void BaseInput(ISdlWindow& window)
{
    InputSystem::Get().Add(SDL_SCANCODE_ESCAPE,
        [&window](KeyState state)
        {
            if (state == KeyState::Pressed)
                window.Close();
        });
}
static std::unique_ptr<Geometry> geometry;
static std::unique_ptr<Texture2d> texture;

void BaseObjects(Scene& scene)
{
    if (!shader.Compile(true))
    {
        std::cout<<"Shader compilation error\n";
        return;
    }
 
    struct Vertex
    {
        float x, y, z;
        float ux, uy;
    };
    
    Vertex triangle[] {
        {-1.0f, -1.0f, 0.f, 0.f, 0.f},
        {-1.0f,  1.0f, 0.f, 0.f, 1.f},
        { 0.0f,  0.0f, 0.f, 0.5f, 0.5f},
    };

    texture.reset(new Texture2d("Assets/image.png"));
    
    geometry.reset(new Geometry(Buffer(DataPtr(triangle, sizeof(triangle)/sizeof(triangle[0]), sizeof(triangle[0])), BufferLayout().Float(3).Float(4))));
    Object& Obj = scene.AddObject(new Object(geometry.get(), &texturedShader, texture.get()));
}

int main(int argc, char** argv)
{
    ISdlWindowParams params;
    params.vsync = true;
    
    OpenglWindow window(params);
    {
        Scene scene;
    
        window.SetBackgroundColor(glm::vec4(0.6, 0.6, 0.6, 1.0));
    
        window.SetScene(&scene);
        BaseInput(window);
        BaseObjects(scene);

        window.Show();
    }
    shader.Destroy();
    vShader.Destroy();
    fShader.Destroy();
    
    return 0;
}

