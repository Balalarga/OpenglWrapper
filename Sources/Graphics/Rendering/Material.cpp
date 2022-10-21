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

void Material::SetUniform(const std::string &name, const int &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniform1i(loc, value);
	}
}

void Material::SetUniform(const std::string &name, const float &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniform1f(loc, value);
	}
}

void Material::SetUniform(const std::string &name, const glm::vec2 &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniform2f(loc, value.x, value.y);
	}
}

void Material::SetUniform(const std::string &name, const glm::vec3 &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniform3f(loc, value.x, value.y, value.z);
	}
}

void Material::SetUniform(const std::string &name, const glm::vec4 &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}
}

void Material::SetUniform(const std::string &name, const glm::mat4 &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
	}
}

void Material::SetUniform(const std::string &name, const glm::mat3 &value)
{
	int loc = GetUniformLocation(name);
	if (loc >= 0)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
	}
}

int Material::GetUniformLocation(const std::string& name)
{
	auto it = _uniformCache.find(name);
	return it != _uniformCache.end() ? it->second : -1;
}
