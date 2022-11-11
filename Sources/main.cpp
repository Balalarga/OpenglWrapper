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

using namespace std;
using namespace Oglw;

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
    

        Texture2dMaterial::VertexData triangle[]
        {
            {{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 0.0f,  0.0f}},
            {{-0.5f,  0.5f, 0.f}, {1.f, 1.f, 0.f, 1.f}, { 0.0f,  1.0f}},
            {{ 0.5f,  0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 1.0f,  1.0f}},
            {{ 0.5f,  0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 1.0f,  1.0f}},
            {{ 0.5f, -0.5f, 0.f}, {1.f, 1.f, 0.f, 1.f}, { 1.0f,  0.0f}},
            {{-0.5f, -0.5f, 0.f}, {1.f, 0.f, 0.f, 1.f}, { 0.0f,  0.0f}},
        };
        baseMat = std::make_shared<Texture2dMaterial>(texture.get());
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