#include "Texture2dMaterial.h"

#include "Graphics/Texture/Texture2d.h"

Texture2dMaterial::Texture2dMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture2d> texture):
	BaseMaterial(std::move(shader)),
	_texture(std::move(texture))
{
}

void Texture2dMaterial::SetupUniforms()
{
	BaseMaterial::SetupUniforms();
	_texture->Bind();
	SetUniform("uTexture", 0);
}
