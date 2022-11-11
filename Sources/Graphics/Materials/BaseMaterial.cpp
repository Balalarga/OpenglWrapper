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

Buffer BaseMaterial::CreateBufferWithLayout(const DataPtr& data)
{
	return { data, BufferLayout().Float(3).Float(4) };
}
}
