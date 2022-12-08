#include "ShaderLoader.h"

#include <SDL_syswm.h>

#include "Files.h"
#include "Graphics/Shading/Shader.h"
#include "Graphics/Shading/ShaderPart.h"

namespace Oglw
{
std::shared_ptr<Shader> ShaderLoader::LoadCode(const std::string& tag,
                                               const std::string& vsh,
                                               const std::string& fsh,
                                               const std::string& gsh)
{
	if (std::shared_ptr<Shader> shader = FindShader(tag))
		return shader;
	
	std::shared_ptr<ShaderPart> gshPart;
	if (!gsh.empty())
		gshPart = std::make_shared<ShaderPart>(ShaderPart::Type::Geometry, vsh);

	return std::make_shared<Shader>(
		std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, vsh),
		std::make_shared<ShaderPart>(ShaderPart::Type::Fragment, fsh),
		gshPart);
}

std::shared_ptr<Shader> ShaderLoader::LoadFiles(const std::string& tag,
                                                const std::string& vPath,
                                                const std::string& fPath,
                                                const std::string& gPath)
{
	if (std::shared_ptr<Shader> shader = FindShader(tag))
		return shader;
	
	const std::string vCode = Files::ReadFile(vPath);
	const std::string fCode = Files::ReadFile(fPath);
	const std::string gCode = gPath.empty() ? "" : Files::ReadFile(gPath);
	if (vCode.empty() || fCode.empty())
		return nullptr;
	
	return LoadCode(tag, vCode, fCode, gCode);
}

ShaderLoader& ShaderLoader::Self()
{
	static ShaderLoader self;
	return self;
}

std::shared_ptr<Shader> ShaderLoader::FindShader(const std::string& tag)
{
	auto it = Self()._shaders.find(tag);
	if (it == Self()._shaders.end())
		return nullptr;
	
	return it->second;
}
}
