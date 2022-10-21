#pragma once
#include <map>
#include <memory>
#include <string>


class Texture2d;

class TextureManager
{
public:
	static TextureManager& Instance();

	std::shared_ptr<Texture2d> GetTexture(const std::string& tag);
	std::shared_ptr<Texture2d> LoadTexture(const std::string& tag, const std::string& filepath);
	
private:
	std::map<std::string, std::shared_ptr<Texture2d>> _textures;
};
