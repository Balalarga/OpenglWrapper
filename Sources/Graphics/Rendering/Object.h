#pragma once
#include "Graphics/Buffers/Buffer.h"

namespace Oglw
{
class IMaterial;

class Object
{
public:
	Object(Buffer vbo, IMaterial* material);
	virtual ~Object();

	void SetMaterial(IMaterial* material);
	
	void Render() const;
	
private:
	unsigned _glHandler;
	
	Buffer _vbo;
	IMaterial* _material;
};
}