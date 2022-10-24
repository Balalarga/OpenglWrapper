#pragma once
#include <map>
#include <memory>
#include <string>

#include "Shader.h"
#include "Uniform.h"


class Shader;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader);

	void Bind() const;
	static void Release();
	
	bool AddUniform(const std::string& name);
	
	void SetUniform(const std::string& name, const UniformValue& value);
	
	int GetUniformLocation(const std::string& name);
	
private:
	std::shared_ptr<Shader> _shader;
	std::map<std::string, int> _uniformCache;
};
