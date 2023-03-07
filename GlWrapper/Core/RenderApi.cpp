#include "RenderApi.h"

#include "RenderTarget.h"

std::vector<RenderTarget*> RenderApi::sTargetsStack;

void RenderApi::PushTarget(RenderTarget* target)
{
	sTargetsStack.push_back(target);
	target->Bind();
}

RenderTarget* RenderApi::PopTarget()
{
	if (sTargetsStack.empty())
		return nullptr;

	RenderTarget* last = sTargetsStack.back();
	last->Release();
	sTargetsStack.pop_back();
	return last;
}

void RenderApi::Clear(int buffers)
{
	glClear(buffers);
}

void RenderApi::Present()
{
	if (!sTargetsStack.empty())
		sTargetsStack.back()->Present();
}
