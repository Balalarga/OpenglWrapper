#pragma once
#include <map>
#include <memory>
#include <string>
#include "ShaderPart.h"

class Shader;

class ShaderManager
{
public:
	static ShaderManager& Instance();


	std::shared_ptr<ShaderPart> GetPart(const std::string& tag);
	std::shared_ptr<ShaderPart> LoadPartFrom(const std::string& tag, ShaderPart::Type type, const std::string& filepath);
	
	std::shared_ptr<Shader> Get(const std::string& tag);
	std::shared_ptr<Shader> LoadFrom(const std::string& tag,
		const std::string& vsh,
		const std::string& fsh,
		const std::string& gsh = "");
	
	std::shared_ptr<Shader> CreateFrom(const std::string& tag,
		const std::string& vsh,
		const std::string& fsh,
		const std::string& gsh = "");

	void CompileAll();
	void CompileParts();
	
private:
	std::map<std::string, std::shared_ptr<ShaderPart>> _parts;
	std::map<std::string, std::shared_ptr<Shader>> _shaders;
};
