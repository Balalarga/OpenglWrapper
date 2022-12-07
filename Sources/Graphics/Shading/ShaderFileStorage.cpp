#include "ShaderFileStorage.h"

#include "JsonConfiger/Archive/JsonArchive.h"

namespace Oglw
{
ShaderFileStorage& ShaderFileStorage::Self()
{
	static ShaderFileStorage storage;
	return storage;
}

void ShaderFileStorage::Serialize(JC::JsonArchive* stream)
{
	stream->Serialize("DefaultShaders", _shaderPaths);
}

void ShaderFileStorage::AddShader(const std::string& tag)
{
	if (GetShader(tag))
		return;

	_shaderPaths[tag] = "";
}

std::string* ShaderFileStorage::GetShader(const std::string& tag)
{
	const auto it = _shaderPaths.find(tag);
	if (it != _shaderPaths.end())
		return &it->second;
	
	return nullptr;
}

ShaderFileStorage::ShaderFileStorage():
	IJsonConfig("Shaders/Defaults.json")
{
}
}
