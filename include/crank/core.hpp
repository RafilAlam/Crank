#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string load_file_content(const std::string &fileName);
void debug_shader(std::string shaderName, GLuint shader);

namespace crank {



}
