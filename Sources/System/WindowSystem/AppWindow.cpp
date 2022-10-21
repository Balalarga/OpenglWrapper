#include "AppWindow.h"
#include "WindowSystem.h"
#include "Graphics/Rendering/IRender.h"
#include "Input/InputManager.h"

AppWindow::AppWindow(const Params& params, WindowSystem& windowSystem):
	_params(params),
	_windowSystem(windowSystem),
	_inputManager(InputManager::Instance())
{
	_sdlWindow = SDL_CreateWindow(_params.title.c_str(),
		_params.pos.x,
		_params.pos.y,
		_params.size.x,
		_params.size.y,
		_params.sdlFlags);
}

AppWindow::~AppWindow()
{
    SDL_DestroyWindow(_sdlWindow);
}

void AppWindow::Show()
{
	SDL_ShowWindow(_sdlWindow);

	_bShouldClose = false;
	while (!_bShouldClose)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			HandleEvents(event);

		if (IRender* render = _windowSystem.GetRender())
		{
			render->Clear();
			render->Render();
			render->Present();
		}
	}
}

void AppWindow::HandleEvents(SDL_Event& event)
{
	// ImGui_ImplSDL2_ProcessEvent(&event);
	switch(event.type)
	{
	case SDL_QUIT:
		{
			_bShouldClose = true;
		}
		break;
	case SDL_WINDOWEVENT:
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE &&
				event.window.windowID == SDL_GetWindowID(_sdlWindow))
					_bShouldClose = true;
		}
		break;
	case SDL_KEYDOWN:
		{
			_inputManager.OnStateChange(event.key.keysym.scancode,
				event.key.repeat == 0 ? KeyState::Pressed : KeyState::Repeated);
		}
		break;
	case SDL_KEYUP:
		{
			_inputManager.OnStateChange(event.key.keysym.scancode, KeyState::Released);
		}
		break;
	default:
		break;
	}
}
