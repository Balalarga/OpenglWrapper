#pragma once
#include "IMaterial.h"
#include "Graphics/Buffers/Buffer.h"

namespace Oglw
{
class BaseMaterial: public IMaterial
{
public:
	BaseMaterial(std::shared_ptr<Shader> shader);
	
	void Prepare() override;
	
	Buffer CreateBufferWithLayout(const DataPtr& data) override;

	void SetColor(glm::vec4 color) { _color = color; }
	
private:
	glm::vec4 _color;
};
}
