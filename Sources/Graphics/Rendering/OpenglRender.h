#pragma once
#include "IRender.h"
#include <SDL_video.h>

class OpenglRender: public IRender
{
public:
	OpenglRender(SDL_Window* window);
	
	void Clear() override;
	void Render() override;
	void Present() override;

	void SetClearColor(const SDL_Color& color);
	
private:
	SDL_Window* _window;
	SDL_Color _backColor{60, 60, 60, 255};
};
