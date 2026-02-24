#include <crank/core.hpp>

std::string load_file_content(const std::string &fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cout << "FAILED TO FETCH " << fileName << " FILE CONTENTS" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string line{}, content{};
  while (std::getline(file, line)) {
    content += line + '\n';
  }

  return content;
}

void debug_shader(std::string shaderName, GLuint shader) {
  GLint shader_compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
  if (!shader_compiled) {
    GLsizei log_length{0};
    GLchar message[1024];
    glGetShaderInfoLog(shader, 1024, &log_length, message);
    std::cout << "SHADER COMPILATION ERROR(" + shaderName + "):\n" + message << std::endl;
  }
}

namespace crank {



}
