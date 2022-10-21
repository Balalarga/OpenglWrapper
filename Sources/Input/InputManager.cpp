#include "InputManager.h"

InputManager& InputManager::Instance()
{
	static InputManager selfInstance;
	return selfInstance;
}

void InputManager::Add(SDL_Scancode code, const std::function<void(const KeyState&)>& callback)
{
	KeyCallbacks[code].push_back(callback);
}

bool InputManager::Remove(SDL_Scancode code, const std::function<void(const KeyState&)>& callback)
{
	for (size_t i = 0; i < KeyCallbacks[code].size(); ++i)
	{
		if (KeyCallbacks[code][i].target<void(const KeyState&)>() == callback.target<void(const KeyState&)>())
		{
			KeyCallbacks[code].erase(KeyCallbacks[code].begin() + i);
			return true;
		}
	}

	return false;
}


void InputManager::OnStateChange(SDL_Scancode code, KeyState state) const
{
	for (const std::function<void(const KeyState&)>& func : KeyCallbacks[code])
		func(state);
}
