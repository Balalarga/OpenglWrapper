#include "Texture2d.h"
#include "OpenGL/ErrorHandle.h"

#include "ThirdParty/stb/stb_image.h"

Texture2d::Texture2d(const glm::ivec2& size, unsigned char* data):
	_handler(0),
	_size(size),
	_pixelFormat(GL_RGBA8),
	_channelCount(4)
{
	_totalSize = _size.x*_size.y*_channelCount;
	
	glGenTextures(1, &_handler);
	glBindTexture(GL_TEXTURE_2D, _handler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, _pixelFormat, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	Release();
}

Texture2d::Texture2d(const std::string& filepath):
	_pixelFormat(GL_RGBA8)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filepath.c_str(), &_size.x, &_size.y, &_channelCount, 0);

	_totalSize = _size.x*_size.y*_channelCount;
	
	glGenTextures(1, &_handler);
	glBindTexture(GL_TEXTURE_2D, _handler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))
	if (image)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, _pixelFormat, _size.x, _size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image))
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	Release();
	
	if (image)
		stbi_image_free(image);
}

Texture2d::~Texture2d()
{
	GLCall(glDeleteTextures(1, &_handler))
}

void Texture2d::Bind(unsigned slotId) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slotId))
	GLCall(glBindTexture(GL_TEXTURE_2D, _handler))
}

void Texture2d::Release()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0))
}

bool Texture2d::UpdateTexture(const std::vector<unsigned char>& rawData) const
{
	if (rawData.size() != _totalSize)
		return false;
	
	Bind();
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, _pixelFormat, _size.x, _size.y, 0, _pixelFormat, GL_UNSIGNED_BYTE, rawData.data()))
	return true;
}

bool Texture2d::UpdateTexture(unsigned char* rawData, size_t count) const
{
	if (count != _totalSize)
		return false;
	
	Bind();
	GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _size.x, _size.y, GL_RGBA, GL_UNSIGNED_BYTE, rawData))
	return true;
}
