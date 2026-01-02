#include <fstream>
#include <sstream>
#include <iostream>

std::string fetchShader(std::string fileName)
{
	std::stringstream buffer;
	std::ifstream file(fileName);
	if (!file) std::cerr << "Failed to open Shader File" << std::endl;

	buffer << file.rdbuf();
	return buffer.str();
}