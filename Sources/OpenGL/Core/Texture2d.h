#pragma once
#include <string>
#include <vector>
#include <glm/vec2.hpp>

class Texture2d
{
public:
	Texture2d(const glm::ivec2& size, unsigned char* data = nullptr);
	Texture2d(const std::string& filepath);
	~Texture2d();

	void Bind(unsigned slotId = 0) const;
	static void Release();

	bool UpdateTexture(const std::vector<unsigned char>& rawData) const;
	bool UpdateTexture(unsigned char* rawData, size_t count) const;

	int GetChannelCount() const { return _channelCount; }
	int GetPixelFormat() const { return _pixelFormat; }
	glm::ivec2 GetSize() const { return _size; }
	size_t GetBufferSize() const { return _totalSize; }

private:
	unsigned _handler;
	glm::ivec2 _size;
	int _pixelFormat;
	int _channelCount;
	
	size_t _totalSize;
};
