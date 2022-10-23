#pragma once
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Shading/Material.h"
#include "Graphics/Texture/Texture2d.h"

class Object
{
public:
	Object(const Buffer& _vbo, const Material& _material, Texture2d* texture = nullptr);
	virtual ~Object();

	void Render() const;
	
private:
	unsigned _glHandler;
	Buffer _vbo;
	Material _material;
	Texture2d* _texture;
};
