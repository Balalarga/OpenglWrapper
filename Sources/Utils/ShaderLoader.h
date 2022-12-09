#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <cereal/cereal.hpp>

#include "CerealTypes.h"

namespace Oglw
{
class Shader;

struct ShaderVariableInfo
{
	std::string type;
	std::string name;
	int id = -1;

	CEREAL_SAVE({
		archive(CEREAL_NVP(name), CEREAL_NVP(type), CEREAL_NVP(id));
	})
	CEREAL_LOAD({
		archive(CEREAL_NVP(name), CEREAL_NVP(type), CEREAL_NVP(id));
	})
};
struct ShaderPartInfo
{
	std::string filepath;
	std::string defaultCode;
	std::vector<ShaderVariableInfo> inputs;
	std::vector<ShaderVariableInfo> outputs;
	std::vector<ShaderVariableInfo> uniforms;

	CEREAL_SAVE({
		archive(CEREAL_NVP(filepath), CEREAL_NVP(inputs), CEREAL_NVP(outputs), CEREAL_NVP(uniforms));
	})
	CEREAL_LOAD({
		archive(CEREAL_NVP(filepath), CEREAL_NVP(inputs), CEREAL_NVP(outputs), CEREAL_NVP(uniforms));
	})
};
struct ShaderInfo
{
	ShaderPartInfo vertexPart;
	ShaderPartInfo fragmentPart;
	ShaderPartInfo geometryPart;

	CEREAL_LOAD({
		archive(CEREAL_NVP(vertexPart), CEREAL_NVP(fragmentPart));

		if (!geometryPart.filepath.empty())
			archive(CEREAL_NVP(geometryPart));
	})

	CEREAL_SAVE({
		archive(CEREAL_NVP(vertexPart), CEREAL_NVP(fragmentPart));

		if (!geometryPart.filepath.empty())
			archive(CEREAL_NVP(geometryPart));
	})
};

class ShaderLoader
{
public:
	static std::string sShadersDirectory;
	static std::string sConfigFile;

	static ShaderLoader& Self();

	static std::string GetFullShaderPath(const std::string& configPath);

	static std::shared_ptr<Shader> TryGetShader(const std::string& tag, const ShaderInfo& defaultInfo);
	static std::shared_ptr<Shader> FindShader(const std::string& tag);

	static std::map<std::string, ShaderInfo*> UpdateShaders();

	static bool LoadDefaultConfig();
	static bool SaveDefaultConfig();

protected:
	static std::shared_ptr<Shader> LoadCode(const std::string& vsh, const std::string& fsh, const std::string& gsh);
	static std::shared_ptr<Shader> LoadFiles(const std::string& vPath, const std::string& fPath, const std::string& gPath);
	static std::shared_ptr<Shader> LoadFromInfo(const ShaderInfo& info);

private:
	ShaderLoader() = default;
	struct ShaderAndInfo
	{
		ShaderInfo info;
		std::shared_ptr<Shader> shader;
		CEREAL_LOAD({
			archive(info);
		})
		CEREAL_SAVE({
			archive(info);
		})
	};
	std::map<std::string, ShaderAndInfo> _shaders;
	bool _bWasChanged = false;
};
}
