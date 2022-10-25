#pragma once
#include "BaseMaterial.h"

class Texture2d;

class Texture2dMaterial: public BaseMaterial
{
public:
	Texture2dMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture2d> texture);

	void SetupUniforms() override;

private:
	std::shared_ptr<Texture2d> _texture;
};
