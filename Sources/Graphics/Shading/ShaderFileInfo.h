#pragma once
#include <map>
#include <string>

namespace Oglw
{

struct ShaderFileInOutVar
{
	std::string type;
	int location;
};

struct ShaderFileMeta
{
	std::map<std::string, ShaderFileInOutVar> inputs;
	std::map<std::string, ShaderFileInOutVar> outputs;
	std::map<std::string, std::string> uniforms; // name, type
};

struct ShaderFileInfo
{
	std::map<std::string, ShaderFileMeta> shaders;
};

struct ShaderProgramFileInfo
{
	std::map<std::string, std::string> shaders; // shader type, shader filepath
};
}
