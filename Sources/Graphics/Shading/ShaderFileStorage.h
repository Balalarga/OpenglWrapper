#pragma once
#include <map>

#include "JsonConfiger/Config/IJsonConfig.h"

namespace Oglw
{
class ShaderFileStorage: public JC::IJsonConfig
{
public:
	static ShaderFileStorage& Self();
	
	void Serialize(JC::JsonArchive* stream) override;
	
	void AddShader(const std::string& tag);
	std::string* GetShader(const std::string& tag);
	
	
private:
	ShaderFileStorage();

	std::map<std::string, std::string> _shaderPaths;
};
}
