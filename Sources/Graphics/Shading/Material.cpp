#include "Material.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

Material::Material(std::shared_ptr<Shader> Material):
	_shader(std::move(Material))
{
}

void Material::Bind() const
{
	_shader->Bind();
}

void Material::Release()
{
	Shader::Release();
}

bool Material::AddUniform(const std::string& name)
{
	int loc = _shader->GetUniformLocation(name);
	if (loc < 0)
		return false;

	_uniformCache[name] = loc;
	return true;
}

void Material::SetUniform(const std::string &name, const UniformValue& value)
{
	int loc = GetUniformLocation(name);
	if (loc < 0)
		return;
	
	std::visit([&](auto&& arg)
	{
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, unsigned>)
			glUniform1ui(loc, arg);
		else if constexpr (std::is_same_v<T, int>)
			glUniform1i(loc, arg);
		else if constexpr (std::is_same_v<T, float>)
			glUniform1f(loc, arg);
		else if constexpr (std::is_same_v<T, glm::vec2>)
			glUniform2f(loc, arg.x, arg.y);
		else if constexpr (std::is_same_v<T, glm::vec3>)
			glUniform3f(loc, arg.x, arg.y, arg.z);
		else if constexpr (std::is_same_v<T, glm::vec4>)
			glUniform4f(loc, arg.x, arg.y, arg.z, arg.w);
		else if constexpr (std::is_same_v<T, glm::mat2>)
			glUniformMatrix2fv(loc, 1, GL_FALSE, &arg[0][0]);
		else if constexpr (std::is_same_v<T, glm::mat3>)
			glUniformMatrix3fv(loc, 1, GL_FALSE, &arg[0][0]);
		else if constexpr (std::is_same_v<T, glm::mat4>)
			glUniformMatrix4fv(loc, 1, GL_FALSE, &arg[0][0]);
	}, value);
}

int Material::GetUniformLocation(const std::string& name)
{
	auto it = _uniformCache.find(name);
	return it != _uniformCache.end() ? it->second : -1;
}
