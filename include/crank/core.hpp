#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string load_file_content(const std::string &fileName);
void debug_shader(std::string shaderName, GLuint shader);
void debug_program(std::string programName, GLuint program);

namespace crank {

void error(std::string msg);

class Window {
private:
public:
  int width, height;
  GLFWwindow* handle;
  Window(std::string name, int p_width, int p_height);
};

class Object {
private:
public:
  GLuint VAO, VBO, EBO, program;
  std::vector<float> vertices;
  std::vector<uint32_t> indices;
  Object(std::vector<float> &vertices, std::vector<uint32_t> &indices);
  void Draw();
};

class Renderer2D {
private:
public:
  GLuint VAO, VBO, EBO, program;
  Window window;
  std::unordered_map<std::string, Object> Objects;
  Renderer2D(Window &window);

  std::function<void()> PreRenderStep = [](){};
  void RenderStep();
  void Run();

  void Create(std::string name, std::vector<float> &vertices, std::vector<uint32_t> &indices);
};

}
