#pragma once
#include <string>
#include <SDL_events.h>


namespace Oglw
{
class InputManager;
class WindowSystem;
class IRender;

class AppWindow
{
public:
	struct Params
	{
		const std::string title;
		SDL_Point pos{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
		SDL_Point size{1280, 720};
		unsigned sdlFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_HIDDEN;
	};
	AppWindow(const Params& params, WindowSystem& windowSystem);
	~AppWindow();

	void Show();
	
	void HandleEvents(SDL_Event& event);
	
	bool ShouldClose() const { return _bShouldClose; }

	SDL_Window* GetInnerWindow() const { return _sdlWindow; }

	const Params& GetParams() const { return _params; }
	
private:
	Params _params;
	WindowSystem& _windowSystem;
	InputManager& _inputManager;
	bool _bShouldClose = false;
	
	SDL_Window* _sdlWindow;
};
}