#pragma once

#include <functional>
#include <SDL.h>

enum class KeyState
{
	Pressed, Released, Repeated
};

class InputManager
{
	friend class AppWindow;
public:
	static InputManager& Instance();

	void Add(SDL_Scancode code, const std::function<void(const KeyState&)>& callback);
	bool Remove(SDL_Scancode code, const std::function<void(const KeyState&)>& callback);

protected:
	InputManager() = default;

	void OnStateChange(SDL_Scancode code, KeyState state) const;

private:
	std::vector<std::function<void(const KeyState&)>> KeyCallbacks[SDL_NUM_SCANCODES];
};
