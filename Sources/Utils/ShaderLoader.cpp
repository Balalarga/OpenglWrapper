#include "ShaderLoader.h"

#include <filesystem>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

#include "Files.h"
#include "Graphics/Shading/Shader.h"
#include "Graphics/Shading/ShaderPart.h"

namespace Oglw
{
std::string ShaderLoader::sShadersDirectory = "../Assets/Shaders";
std::string ShaderLoader::sConfigFile = "DefaultShaders.json";

static const std::string shadersDirectoryCache = ShaderLoader::sShadersDirectory;

std::shared_ptr<Shader> ShaderLoader::LoadCode(const std::string& vsh,
                                               const std::string& fsh,
                                               const std::string& gsh)
{
	std::shared_ptr<ShaderPart> gshPart;
	if (!gsh.empty())
		gshPart = std::make_shared<ShaderPart>(ShaderPart::Type::Geometry, vsh);

	return std::make_shared<Shader>(
		std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, vsh),
		std::make_shared<ShaderPart>(ShaderPart::Type::Fragment, fsh),
		gshPart);
}

std::shared_ptr<Shader> ShaderLoader::LoadFiles(const std::string& vPath,
                                                const std::string& fPath,
                                                const std::string& gPath)
{
	const std::string vCode = Files::ReadFile(GetFullShaderPath(vPath));
	const std::string fCode = Files::ReadFile(GetFullShaderPath(fPath));
	const std::string gCode = gPath.empty() ? "" : Files::ReadFile(GetFullShaderPath(gPath));
	if (vCode.empty() || fCode.empty())
		return nullptr;

	return LoadCode(vCode, fCode, gCode);
}

std::shared_ptr<Shader> ShaderLoader::LoadFromInfo(const ShaderInfo& info)
{
	return LoadCode(info.vertexPart.defaultCode, info.fragmentPart.defaultCode, info.geometryPart.defaultCode);
}

ShaderLoader& ShaderLoader::Self()
{
	static ShaderLoader self;
	return self;
}

std::string ShaderLoader::GetFullShaderPath(const std::string& configPath)
{
	std::filesystem::path path(sShadersDirectory);
	path.append(configPath);
	return path.generic_string();
}

std::shared_ptr<Shader> ShaderLoader::TryGetShader(const std::string& tag, const ShaderInfo& defaultInfo)
{
	if (std::shared_ptr<Shader> shader = FindShader(tag))
		return shader;

	const auto& val = Self()._shaders.insert_or_assign(tag, ShaderAndInfo{defaultInfo, LoadFromInfo(defaultInfo)});
	Self()._bWasChanged = true;

	return val.first->second.shader;
}

std::shared_ptr<Shader> ShaderLoader::FindShader(const std::string& tag)
{
	const auto it = Self()._shaders.find(tag);
	if (it == Self()._shaders.end())
		return nullptr;
	
	return it->second.shader;
}

std::map<std::string, ShaderInfo*> ShaderLoader::UpdateShaders()
{
	std::map<std::string, ShaderInfo*> invalids;
	for (auto& [tag, data] : Self()._shaders)
	{
		data.shader = LoadFiles(data.info.vertexPart.filepath, data.info.fragmentPart.filepath, data.info.geometryPart.filepath);
		if (!data.shader)
			invalids[tag] = &data.info;
	}

	return invalids;
}

bool ShaderLoader::LoadDefaultConfig()
{
	std::ifstream file(sConfigFile);
	if (!file)
		return false;

	{
		cereal::JSONInputArchive archive(file);
		archive(cereal::make_nvp("RootDirectory", sShadersDirectory));
		archive(cereal::make_nvp("Shaders", Self()._shaders));
	}

	file.close();

	Self()._bWasChanged = false;
	return true;
}

bool ShaderLoader::SaveDefaultConfig()
{
	if (shadersDirectoryCache == sShadersDirectory && !Self()._bWasChanged)
		return true;

	std::ofstream file(sConfigFile);
	if (!file)
		return false;
	{
		cereal::JSONOutputArchive archive(file);
		archive(cereal::make_nvp("RootDirectory", sShadersDirectory));
		archive(cereal::make_nvp("Shaders", Self()._shaders));
	}
	file.close();
	return true;
}
}
