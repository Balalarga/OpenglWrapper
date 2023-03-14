#pragma once
#include <vector>

#include <GL/glew.h>

class RenderTarget;


class RenderApi
{
public:
	RenderApi() = delete;
	RenderApi(RenderApi&&) = delete;
	RenderApi(const RenderApi&) = delete;
	RenderApi& operator=(const RenderApi&) = delete;

	static void PushTarget(RenderTarget* target);
	static RenderTarget* PopTarget();

	static void Clear(int buffers = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	static void Present();


private:
	static std::vector<RenderTarget*> sTargetsStack;
};
