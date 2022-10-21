#include "OpenglSystem.h"

#include <GL/glew.h>

#include "System/WindowSystem/WindowSystem.h"
#include "Utils/Macroses.h"

OpenglSystem::OpenglSystem(const Params& params):
	ISystem(TOSTRING(OpenglSystem)),
	_params(params),
	_glContext()
{
}

bool OpenglSystem::Init(bool bStatus)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, _params.contextFlags);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, _params.contextProfileMask);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, _params.contextMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, _params.contextMinorVersion);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, _params.doubleBuffering);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, _params.depthSize);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, _params.stencilSize);
	
	_glContext = SDL_GL_CreateContext(_params.windowSystem->GetWindow().GetInnerWindow());

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return false;

	SDL_GL_MakeCurrent(_params.windowSystem->GetWindow().GetInnerWindow(), _glContext);
	
	return true;
}

void OpenglSystem::Destroy()
{
    SDL_GL_DeleteContext(_glContext);
}

void OpenglSystem::SetClearColor(const SDL_Color& color)
{
	glClearColor(static_cast<float>(color.r)/255.f,
		static_cast<float>(color.g)/255.f,
		static_cast<float>(color.b)/255.f,
		static_cast<float>(color.a)/255.f);
}

void OpenglSystem::Clear(unsigned buffers)
{
	glClear(buffers);
}
