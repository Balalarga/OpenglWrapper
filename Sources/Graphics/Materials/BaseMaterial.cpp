#include "BaseMaterial.h"

namespace Oglw
{
BaseMaterial::BaseMaterial(std::shared_ptr<Shader> shader):
	IMaterial(std::move(shader)),
	_color(0)
{
}

void BaseMaterial::Prepare()
{
	SetUniform("uColor", _color);
}
}