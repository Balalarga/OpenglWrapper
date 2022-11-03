#include "Files.h"

#include <fstream>
#include <sstream>


namespace Oglw::Files
{
std::string ReadFile(const std::string& filepath)
{
	const std::ifstream file(filepath);
	if (!file)
		return "";

	std::stringstream stream;
	stream << file.rdbuf();
	return stream.str();
}
}
