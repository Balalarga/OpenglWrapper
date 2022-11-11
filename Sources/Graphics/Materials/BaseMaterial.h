#pragma once
#include "IMaterial.h"
#include "Graphics/Buffers/Buffer.h"

namespace Oglw
{
class BaseMaterial: public IMaterial
{
public:
	BaseMaterial(std::shared_ptr<Shader> shader);
	BaseMaterial();
	
	void Prepare() override;
	
	Buffer CreateBufferWithLayout(const DataPtr& data) override;

	void SetModelMatrix(const glm::mat4& matrix) { _modelMatrix = matrix; }
	
private:
	glm::mat4 _modelMatrix;
};
}
