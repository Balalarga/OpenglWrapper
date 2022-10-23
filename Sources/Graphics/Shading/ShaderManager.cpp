#include "ShaderManager.h"

#include "Shader.h"
#include "ShaderPart.h"
#include "Utils/Files.h"

static ShaderManager sSelf;

ShaderManager& ShaderManager::Instance()
{
	return sSelf;
}

std::shared_ptr<ShaderPart> ShaderManager::GetPart(const std::string& tag, ShaderPart::Type type)
{
	const auto it = Instance()._parts[static_cast<uint8_t>(type)].find(tag);
	if (it != Instance()._parts[static_cast<uint8_t>(type)].end())
		return it->second;
	
	return nullptr;
}

std::shared_ptr<ShaderPart> ShaderManager::LoadPartFrom(const std::string& tag, ShaderPart::Type type, const std::string& filepath)
{
	if (std::shared_ptr<ShaderPart> part = GetPart(tag, type))
		return part;
	
	std::string code = Files::ReadFile(filepath);
	if (code.empty())
		return nullptr;

	auto part = std::make_shared<ShaderPart>(type, code);
	Instance()._parts[static_cast<uint8_t>(type)][tag] = part;
	return part;
}

std::shared_ptr<ShaderPart> ShaderManager::LoadPart(const std::string& tag,
	ShaderPart::Type type,
	const std::string& code)
{
	if (std::shared_ptr<ShaderPart> part = GetPart(tag, type))
		return part;
	
	auto part = std::make_shared<ShaderPart>(type, code);
	Instance()._parts[static_cast<uint8_t>(type)][tag] = part;
	return part;
}

std::shared_ptr<Shader> ShaderManager::Get(const std::string& tag)
{
	auto it = Instance()._shaders.find(tag);
	if (it != Instance()._shaders.end())
		return it->second;
	
	return nullptr;
}

std::shared_ptr<Shader> ShaderManager::CreateFrom(const std::string& tag, const std::string& vsh,
                                                  const std::string& fsh, const std::string& gsh)
{
	if (std::shared_ptr<Shader> shader = Get(tag))
		return shader;

	std::shared_ptr<ShaderPart> vshPart = GetPart(vsh, ShaderPart::Type::Vertex);
	std::shared_ptr<ShaderPart> fshPart = GetPart(fsh, ShaderPart::Type::Fragment);
	std::shared_ptr<ShaderPart> gshPart = GetPart(gsh, ShaderPart::Type::Geometry);
	if (!vshPart || !fshPart)
		return nullptr;

	auto shader = std::make_shared<Shader>(vshPart, fshPart, gshPart);
	Instance()._shaders[tag] = shader;
	return shader;
}

std::shared_ptr<Shader> ShaderManager::CreateFrom(const std::string& tag,
	std::shared_ptr<ShaderPart> vsh,
	std::shared_ptr<ShaderPart> fsh,
	std::shared_ptr<ShaderPart> gsh)
{
	if (std::shared_ptr<Shader> shader = Get(tag))
		return shader;

	if (!vsh || !fsh)
		return nullptr;

	auto shader = std::make_shared<Shader>(vsh, fsh, gsh);
	Instance()._shaders[tag] = shader;
	return shader;
}

void ShaderManager::CompileAll()
{
	CompileParts();
	
	for (auto& [tag, shader]: Instance()._shaders)
		shader->Compile();
}

void ShaderManager::CompileParts()
{
	for (const std::map<std::string, std::shared_ptr<ShaderPart>>& typedParts : Instance()._parts)
	{
		for (auto& [tag, part]: typedParts)
			part->Compile();
	}
}
