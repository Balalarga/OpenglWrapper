﻿#pragma once
#include <map>
#include <memory>
#include <string>

#include "Uniform.h"
#include "Utils/CerealTypes.h"


namespace Oglw
{
class ShaderPart;

class Shader
{
public:
	Shader(std::shared_ptr<ShaderPart> vShader,
		   std::shared_ptr<ShaderPart> fShader,
		   std::shared_ptr<ShaderPart> gShader = nullptr);
	~Shader();

	bool Compile();
	void Destroy();

	void Bind() const;
	static void Release();

	void SetUniform(const std::string& name, const UniformValue& value, bool bUnbind = false);

	CEREAL_SERIALIZATION({
		archive();
	})
	
protected:
	int GetUniformLocation(const std::string& name);

private:
	struct
	{
		std::shared_ptr<ShaderPart> vShader;
		std::shared_ptr<ShaderPart> fShader;
		std::shared_ptr<ShaderPart> gShader;
	} _parts;

	unsigned _glHandler = 0;

	std::map<std::string, int> _uniformCache;
};
}
