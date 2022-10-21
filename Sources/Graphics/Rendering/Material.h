#pragma once
#include <map>
#include <memory>
#include <string>
#include <glm/fwd.hpp>

#include "Shader.h"


class Shader;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader);

	void Bind() const;
	static void Release();
	
	bool AddUniform(const std::string& name);
	
	void SetUniform(const std::string& name, const int& value);
	void SetUniform(const std::string& name, const float& value);
	void SetUniform(const std::string& name, const glm::vec2& value);
	void SetUniform(const std::string& name, const glm::vec3& value);
	void SetUniform(const std::string& name, const glm::vec4& value);
	void SetUniform(const std::string& name, const glm::mat4& value);
	void SetUniform(const std::string& name, const glm::mat3& value);
	
	int GetUniformLocation(const std::string& name);
	
private:
	std::shared_ptr<Shader> _shader;
	std::map<std::string, int> _uniformCache;
};
