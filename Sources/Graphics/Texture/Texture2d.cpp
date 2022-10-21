#include "Texture2d.h"

#include <GL/glew.h>

Texture2d::Texture2d(glm::vec2 size, int channels, const unsigned char* data):
	_size(size),
	_channels(channels)
{
	glGenTextures(1, &_glHandler);
	glBindTexture(GL_TEXTURE_2D, _glHandler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	if (_channels == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else if (_channels == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else if (_channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2d::Bind(unsigned slot) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, _glHandler);
}

void Texture2d::Release()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

