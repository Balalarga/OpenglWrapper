#include "ShaderLoader.h"

#include "Graphics/Shading/Shader.h"
#include "Graphics/Shading/ShaderPart.h"

std::shared_ptr<Shader> ShaderLoader::LoadCode(const std::string& vsh,
                                               const std::string& fsh,
                                               const std::string& gsh)
{
	std::shared_ptr<ShaderPart> vshPart = std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, vsh);
	std::shared_ptr<ShaderPart> fshPart = std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, fsh);

	std::shared_ptr<ShaderPart> gshPart;
	if (!gsh.empty())
		gshPart = std::make_shared<ShaderPart>(ShaderPart::Type::Vertex, vsh);

	return std::make_shared<Shader>(vshPart, fshPart, gshPart);
}

std::shared_ptr<Shader> ShaderLoader::LoadFile(const std::string& vPath,
                                               const std::string& fPath,
                                               const std::string& gPath)
{
	
}
