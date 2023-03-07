#include <iostream>

#include "Application.h"
#include "Core/FrameBuffer.h"
#include "Core/LaidVramBuffer.h"
#include "Scene.h"


auto vShader = R"(
#version 330

layout(location = 0) in vec3 iVert;
layout(location = 1) in vec4 iVertColor;

uniform mat4 uMVP = mat4(1);

out vec4 vertColor;

void main()
{
    gl_Position = uMVP * vec4(iVert, 1.0);
    vertColor = iVertColor;
}
)";

auto fShader = R"(
#version 330

in vec4 vertColor;

out vec4 fragColor;

void main()
{
    fragColor = vertColor;
}
)";



class MyApp: public Application
{
public:
    MyApp():
        scene(GetWindow()->GetSize())
    {
        GetInputManager()->Add(SDL_SCANCODE_ESCAPE,
        [](Window& window, const KeyState& state)
        {
            window.Close();
        });

        GetInputManager()->Add(SDL_SCANCODE_W,
        [this](Window& window, const KeyState& state)
        {
            if (state != KeyState::Pressed)
                return;

            scene.GetCamera().Move({0, 0, 0.1});
            std::cout << scene.GetCamera().GetLocation().x << ", ";
            std::cout << scene.GetCamera().GetLocation().y << ", ";
            std::cout << scene.GetCamera().GetLocation().z << "\n";
        });
        GetInputManager()->Add(SDL_SCANCODE_S,
        [this](Window& window, const KeyState& state)
        {
            if (state != KeyState::Pressed)
                return;

            scene.GetCamera().Move({0, 0, -0.1});
            std::cout << scene.GetCamera().GetLocation().x << ", ";
            std::cout << scene.GetCamera().GetLocation().y << ", ";
            std::cout << scene.GetCamera().GetLocation().z << "\n";
        });
        GetInputManager()->AddOnMouseMove([this](Window&, glm::vec2 delta, KeyState keys[5])
        {
            if (keys[SDL_BUTTON_RIGHT-1] == KeyState::Pressed)
            {
                std::cout << delta.x << ", " << delta.y << "\n";
                scene.GetCamera().Rotate({delta.y/100.f, delta.x/100.f, 0});
            }
        });
    }
    void Render() override
    {
        scene.Render();
    }

    void RenderImGui() override
    {

    }

    void Update(float delta) override
    {
        scene.Update(delta);
    }

    Scene scene;
};


int main(int argc, char** argv)
{
    MyApp app;

    std::shared_ptr<Material> mat = std::make_shared<Material>(
        ShaderSourceKit{
            .vertexShader = vShader,
            .fragmentShader = fShader
        });

    if (!*mat)
    {
        std::cout << "Shader compilation error\n";
        return -1;
    }

    struct Vertex
    {
        glm::vec3 pos;
        glm::vec4 color;

        static VramBufferLayout GetVramBufferLayout()
        {
            return VramBufferLayout().Float(3).Float(4);
        }
    };

    std::vector<Vertex> data
    {
        {{-0.5, -0.5, 0}, {1, 1, 1, 1}},
        {{   0,  0.5, 0}, {1, 1, 1, 1}},
        {{ 0.5, -0.5, 0}, {1, 1, 1, 1}},
    };

    std::shared_ptr<SceneObject> object = app.scene.CreateObject<SceneObject>(LaidVramBuffer(data), mat);

    app.Run();

    return 0;
}
