#pragma once
#include <memory>
#include <string>

class Shader;

class ShaderLoader
{
public:
	static std::shared_ptr<Shader> LoadCode(const std::string& vsh,
	                                        const std::string& fsh,
	                                        const std::string& gsh = "");

	static std::shared_ptr<Shader> LoadFile(const std::string& vPath,
											const std::string& fPath,
											const std::string& gPath = "");
};
