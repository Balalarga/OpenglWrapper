#pragma once
#include "Graphics/Shading/Shader.h"

namespace Oglw
{
struct DataPtr;
class Buffer;
}

namespace Oglw
{
class Shader;

class IMaterial
{
public:
	IMaterial(std::shared_ptr<Shader> shader);
	virtual ~IMaterial() = default;
	
	void Bind() const { _shader->Bind(); }
	static void Release() { Shader::Release(); }

	/// Calls between \b Binding and \b Rendering of \b Object
	virtual void Prepare() = 0;

	virtual Buffer CreateBufferWithLayout(const DataPtr& data) = 0;
	
	std::shared_ptr<Shader> GetShader() const { return _shader; }
	void SetShader(std::shared_ptr<Shader> shader);
	
protected:
	void SetUniform(const std::string& name, const UniformValue& value, bool bUnbind = false) const
	{
		_shader->SetUniform(name, value, bUnbind);
	}
	
private:
	std::shared_ptr<Shader> _shader;
};
}
