#pragma once
#include <map>
#include <string>

#include "Uniform.h"


class ShaderPart;

class Shader
{
public:
	Shader(ShaderPart* vShader,
	       ShaderPart* fShader,
	       ShaderPart* gShader = nullptr);
	~Shader();

	bool Compile();
	void Destroy();

	void Bind() const;
	static void Release();

	void SetUniform(const std::string& name, const UniformValue& value, bool bUnbind = false);

protected:
	int GetUniformLocation(const std::string& name);

private:
	struct
	{
		ShaderPart* vShader;
		ShaderPart* fShader;
		ShaderPart* gShader;
	} _parts;

	unsigned _glHandler = 0;

	std::map<std::string, int> _uniformCache;
};
