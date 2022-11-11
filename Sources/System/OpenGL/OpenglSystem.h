#pragma once
#include <SDL_video.h>
#include <GL/glew.h>

#include "System/ISystem.h"

namespace Oglw
{
class WindowSystem;

class OpenglSystem: public ISystem
{
public:
	struct Params
	{
		Params(WindowSystem* windowSystem):
			windowSystem(windowSystem)
		{}
		
		WindowSystem* windowSystem;
		int contextFlags = 0;
		int contextProfileMask = SDL_GL_CONTEXT_PROFILE_CORE;
		int contextMajorVersion = 4;
		int contextMinorVersion = 5;
		int doubleBuffering = 1;
		int depthSize = 24;
		int stencilSize = 8;
	};
	OpenglSystem(const Params& params);

	const SDL_GLContext& GetContext() const { return _glContext; }
	bool Init() override;
	void Destroy() override;

	// OpenglWrapping
	static void SetClearColor(const SDL_Color& color);

private:
	Params _params;
	SDL_GLContext _glContext;
};
}