#pragma once
#include "RenderTarget.h"
#include "Texture.h"


class FrameBuffer: public VramHandle, public RenderTarget
{
public:
	FrameBuffer(const Texture& texture);
	FrameBuffer(glm::ivec2 size, int channels);
	virtual ~FrameBuffer();

	// VramHandle interface
	bool Init() override;

	// RenderTarget interface
	void Bind() override;
	void Release() override;
	void Present() override;


protected:
	int AllocateVram() override;
	void DeallocateVram() override;


private:
	Texture _texture;
};
