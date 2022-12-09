#pragma once
#include "BaseMaterial.h"

namespace Oglw
{
class Texture2d;

class Texture2dMaterial: public BaseMaterial
{
public:
	struct VertexData
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 uv;
	};
	Buffer CreateBufferWithLayout(const DataPtr& data) override;
	Texture2dMaterial(std::shared_ptr<Shader> shader, Texture2d* texture);
	Texture2dMaterial(Texture2d* texture);

	void Prepare() override;

	static ShaderInfo sDefaultShaderInfo;

private:
	Texture2d* _texture;
};
}
