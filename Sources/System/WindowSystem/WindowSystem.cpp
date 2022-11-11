#include "WindowSystem.h"

namespace Oglw
{
WindowSystem::WindowSystem(const Params& params):
	ISystem(TOSTRING(WindowSystem)),
	_params(params)
{
}

bool WindowSystem::Init()
{
	_window = std::make_unique<AppWindow>(_params.windowParams, *this);
	return true;
}

void WindowSystem::Destroy()
{
	_window.reset();
}
}