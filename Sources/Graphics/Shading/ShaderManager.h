#pragma once
#include <array>
#include <map>
#include <memory>
#include <string>
#include "ShaderPart.h"

class Shader;

class ShaderManager
{
public:
	static ShaderManager& Instance();

	static std::shared_ptr<ShaderPart> GetPart(const std::string& tag, ShaderPart::Type type);
	static std::shared_ptr<ShaderPart> LoadPartFrom(const std::string& tag, ShaderPart::Type type, const std::string& filepath);
	static std::shared_ptr<ShaderPart> LoadPart(const std::string& tag, ShaderPart::Type type, const std::string& code);
    
	static std::shared_ptr<Shader> Get(const std::string& tag);
	static std::shared_ptr<Shader> CreateFrom(const std::string& tag,
		const std::string& vsh,
		const std::string& fsh,
		const std::string& gsh = "");
	static std::shared_ptr<Shader> CreateFrom(const std::string& tag,
		std::shared_ptr<ShaderPart> vsh,
		std::shared_ptr<ShaderPart> fsh,
		std::shared_ptr<ShaderPart> gsh = nullptr);

	static void CompileAll();
	static void CompileParts();
	
private:
	std::array<std::map<std::string, std::shared_ptr<ShaderPart>>, static_cast<size_t>(ShaderPart::Type::Count)> _parts;
	std::map<std::string, std::shared_ptr<Shader>> _shaders;
};
