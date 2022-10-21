#include "ShaderManager.h"

#include "Shader.h"
#include "ShaderPart.h"
#include "Utils/Files.h"

ShaderManager& ShaderManager::Instance()
{
	static ShaderManager manager;
	return manager;
}

std::shared_ptr<ShaderPart> ShaderManager::GetPart(const std::string& tag)
{
	auto it = _parts.find(tag);
	if (it != _parts.end())
		return it->second;
	
	return nullptr;
}

std::shared_ptr<ShaderPart> ShaderManager::LoadPartFrom(const std::string& tag, ShaderPart::Type type, const std::string& filepath)
{
	if (std::shared_ptr<ShaderPart> part = GetPart(tag))
		return part;
	
	std::string code = Files::ReadFile(filepath);
	if (code.empty())
		return nullptr;

	auto part = std::make_shared<ShaderPart>(type, code);
	_parts[tag] = part;
	return part;
}

std::shared_ptr<Shader> ShaderManager::Get(const std::string& tag)
{
	auto it = _shaders.find(tag);
	if (it != _shaders.end())
		return it->second;
	
	return nullptr;
}

std::shared_ptr<Shader> ShaderManager::CreateFrom(const std::string& tag, const std::string& vsh,
	const std::string& fsh, const std::string& gsh)
{
	if (std::shared_ptr<Shader> shader = Get(tag))
		return shader;

	std::shared_ptr<ShaderPart> vshPart = GetPart(vsh);
	std::shared_ptr<ShaderPart> fshPart = GetPart(fsh);
	std::shared_ptr<ShaderPart> gshPart = GetPart(gsh);
	if (!vshPart || !fshPart)
		return nullptr;

	auto shader = std::make_shared<Shader>(vshPart, fshPart, gshPart);
	_shaders[tag] = shader;
	return shader;
}

void ShaderManager::CompileAll()
{
	CompileParts();
	
	for (auto& [tag, shader]: _shaders)
		shader->Compile();
}

void ShaderManager::CompileParts()
{
	for (auto& [tag, part]: _parts)
		part->Compile();
}
