#pragma once
#include "Graphics/Buffers/Buffer.h"
#include "Graphics/Materials/IMaterial.h"

class Object
{
public:
	Object(Buffer vbo, IMaterial* material);
	virtual ~Object();
	
	void Render() const;
	
private:
	unsigned _glHandler;
	
	Buffer _vbo;
	IMaterial* _material;
};
