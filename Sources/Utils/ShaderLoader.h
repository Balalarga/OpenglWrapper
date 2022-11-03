#pragma once
#include <memory>
#include <string>

namespace Oglw
{
class Shader;

class ShaderLoader
{
public:
	static std::shared_ptr<Shader> LoadCode(const std::string& vsh,
											const std::string& fsh,
											const std::string& gsh = "");

	static std::shared_ptr<Shader> LoadFiles(const std::string& vPath,
											 const std::string& fPath,
											 const std::string& gPath = "");
};
}