#include "OpenglRender.h"

#include <cassert>
#include <GL/glew.h>
#include "System/OpenGL/OpenglSystem.h"

OpenglRender::OpenglRender(SDL_Window* window):
	_window(window)
{
	assert(window);
}

void OpenglRender::Clear()
{
	OpenglSystem::SetClearColor(_backColor);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRender::Render()
{
	
}

void OpenglRender::Present()
{
	SDL_GL_SwapWindow(_window);
}

void OpenglRender::SetClearColor(const SDL_Color& color)
{
	_backColor = color;
	OpenglSystem::SetClearColor(_backColor);
}
