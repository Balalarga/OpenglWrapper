#include "Files.h"

#include <fstream>
#include <sstream>
#include <filesystem>


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

void CreateOrOpenFile(std::ofstream& stream, const std::string& filepath)
{
	// std::filesystem::create_directories({filepath});
	stream.open(filepath);
}
}
