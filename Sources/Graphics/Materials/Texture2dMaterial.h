#pragma once
#include "BaseMaterial.h"

namespace Oglw
{
class Texture2d;

class Texture2dMaterial: public BaseMaterial
{
public:
	Texture2dMaterial(std::shared_ptr<Shader> shader, Texture2d* texture);

	void Prepare() override;

private:
	Texture2d* _texture;
};
}