#include <crank/core.hpp>

namespace crank {
  Shader::Shader(std::string fileName): handle(glCreateShader()) {
    const char* shadercontent = fetchShader(fileName);
    glShaderSource(handle, 1, &shadercontent, NULL);
    glCompileShader(handle);
  }

  ShaderProgram::ShaderProgram(): handle(glCreateProgram()) {}
  ShaderProgram::AttachShader(GLuint shader) {
    glAttachShader(handle, shader.handle);
  }
  ShaderProgram::Link() {
    glLinkProgram(handle);
  }

  Window::Window() {
    if (!glfwInit()) {
      std::cout << "GLFW couldn't start" << std::endl;
      std::exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  }
}
