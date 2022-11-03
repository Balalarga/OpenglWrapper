#include "Texture2dMaterial.h"

#include "Graphics/Texture/Texture2d.h"

namespace Oglw
{
Texture2dMaterial::Texture2dMaterial(std::shared_ptr<Shader> shader, Texture2d* texture):
	BaseMaterial(std::move(shader)),
	_texture(texture)
{
}

void Texture2dMaterial::Prepare()
{
	BaseMaterial::Prepare();
	_texture->Bind();
	SetUniform("uTexture", 0);
}
}