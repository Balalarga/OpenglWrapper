#include "ShaderLoader.h"

#include "Files.h"
#include "Graphics/Shading/Shader.h"
#include "Graphics/Shading/ShaderPart.h"

namespace Oglw
{
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
	const std::string vCode = Files::ReadFile(vPath);
	const std::string fCode = Files::ReadFile(fPath);
	const std::string gCode = gPath.empty() ? "" : Files::ReadFile(gPath);
	if (vCode.empty() || fCode.empty())
		return nullptr;
	
	return LoadCode(vCode, fCode, gCode);
}
}