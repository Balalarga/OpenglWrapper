#include "IMaterial.h"

IMaterial::IMaterial(std::shared_ptr<Shader> shader):
	_shader(std::move(shader))
{
}

void IMaterial::Bind() const
{
	_shader->Bind();
}

void IMaterial::Release()
{
	Shader::Release();
}
