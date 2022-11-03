#include "SystemManager.h"

#include "ImGui/ImGuiSystem.h"
#include "OpenGL/OpenglSystem.h"
#include "Sdl/SdlSystem.h"
#include "WindowSystem/WindowSystem.h"

namespace Oglw
{
static SystemManager sSelf;

SystemManager& SystemManager::Instance()
{
	return sSelf;
}

SystemManager& SystemManager::Init()
{
	if (!sSelf.sdlSystem)
		InitDefaults();
	
	for (const std::unique_ptr<ISystem>& system : sSelf._systems)
		system->SetWasInit(system->Init(system->WasInit()));
	
	return sSelf;
}

void SystemManager::Destroy()
{
	for (auto it = sSelf._systems.rbegin(); it != sSelf._systems.rend(); ++it)
	{
		if ((*it)->WasInit())
			(*it)->Destroy();
	}
}

void SystemManager::InitDefaults()
{
	SdlSystem::Params sdlParams;
	sSelf.sdlSystem = &CreateSystem<SdlSystem>(sdlParams);
	
	WindowSystem::Params windowParams;
	sSelf.windowSystem = &CreateSystem<WindowSystem>(windowParams);
	
	OpenglSystem::Params openglParams(sSelf.windowSystem);
	sSelf.openglSystem = &CreateSystem<OpenglSystem>(openglParams);
	
	ImGuiSystem::Params imguiParams(sSelf.windowSystem, sSelf.openglSystem);
	sSelf.imguiSystem = &CreateSystem<ImGuiSystem>(imguiParams);	
}
}