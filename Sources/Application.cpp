#include "Application.h"

#include "System/SystemManager.h"
#include "System/WindowSystem/AppWindow.h"
#include "System/WindowSystem/WindowSystem.h"

namespace Oglw
{
Application::Application():
	_systemManager(SystemManager::Init())
{
}

Application::~Application()
{
	SystemManager::Destroy();
}

void Application::Run()
{
	Init();
	
	_systemManager.windowSystem->GetWindow().Show();
	
	Destroy();
}
}
