#pragma once
#include <map>
#include <memory>
#include <string>

namespace Oglw
{
class Shader;

class ShaderLoader
{
public:
	static ShaderLoader& Self();
	
	static std::shared_ptr<Shader> LoadCode(const std::string& tag,
											const std::string& vsh,
											const std::string& fsh,
											const std::string& gsh = "");

	static std::shared_ptr<Shader> LoadFiles(const std::string& tag,
	                                         const std::string& vPath,
	                                         const std::string& fPath,
	                                         const std::string& gPath = "");

	static std::shared_ptr<Shader> FindShader(const std::string& tag);

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(_shaders);
	}
	
private:
	ShaderLoader() = default;
	std::map<std::string, std::shared_ptr<Shader>> _shaders;
};
}