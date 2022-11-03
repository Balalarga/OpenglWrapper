#pragma once
#include "glm/glm.hpp"

namespace Oglw
{
class Texture2d
{
public:
	Texture2d(glm::vec2 size, int channels, const unsigned char* data);

	void Bind(unsigned slot = 0) const;
	static void Release();
	
private:
	glm::vec2 _size;
	int _channels;
	unsigned _glHandler;
};
}