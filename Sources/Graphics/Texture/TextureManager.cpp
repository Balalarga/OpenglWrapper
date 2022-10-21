#include "TextureManager.h"

#include <glm/vec2.hpp>
#include "Texture2d.h"
#include "ThirdParty/stb/stb_image.h"

TextureManager& TextureManager::Instance()
{
	static TextureManager manager;
	return manager;
}

std::shared_ptr<Texture2d> TextureManager::GetTexture(const std::string& tag)
{
	const auto it = _textures.find(tag);
	if (it != _textures.end())
		return it->second;
	
	return nullptr;
}

std::shared_ptr<Texture2d> TextureManager::LoadTexture(const std::string& tag, const std::string& filepath)
{
	if (std::shared_ptr<Texture2d> existingTexture = GetTexture(tag))
		return existingTexture;
	
	stbi_set_flip_vertically_on_load(true);
	glm::ivec2 size;
	int channels;
	stbi_uc* imageData = stbi_load(filepath.c_str(), &size.x, &size.y, &channels, 0);

	if (!imageData)
		return nullptr;

	_textures[tag] = std::make_shared<Texture2d>(size, channels, imageData);

	stbi_image_free(imageData);
	return _textures[tag];
}
