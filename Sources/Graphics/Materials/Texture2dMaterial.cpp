#include "Texture2dMaterial.h"

#include "Graphics/Texture/Texture2d.h"

Texture2dMaterial::Texture2dMaterial(std::shared_ptr<Shader> shader, Texture2d* texture):
	BaseMaterial(std::move(shader)),
	_texture(texture)
{
}

void Texture2dMaterial::SetupUniforms()
{
	BaseMaterial::SetupUniforms();
	_texture->Bind();
	SetUniform("uTexture", 0);
}
