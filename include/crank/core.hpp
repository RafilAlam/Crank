#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::string load_file_content(const std::string &fileName);
void debug_shader(std::string shaderName, GLuint shader);
void debug_program(std::string programName, GLuint program);

namespace crank {

void error(std::string msg);

class Window {
private:
  std::unordered_map<int, std::function<void()>> keybinds;
public:
  int width, height;
  GLFWwindow* handle;
  Window(std::string name, int p_width, int p_height);
  void Keybind(int key, std::function<void()> callback); // key is GLFW key tokens
};

class Object {
private:
  struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale    = glm::vec3(1.0f);

    glm::mat4 GetMatrix() {
      glm::mat4 model(1.0f);
      model = glm::translate(model, position);
      model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
      model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::scale(model, scale);
      return model;
    }
  };
public:
  GLuint VAO, VBO, EBO, program;
  std::vector<float> vertices;
  std::vector<uint32_t> indices;
  Transform transform;

  Object(std::vector<float> &vertices, std::vector<uint32_t> &indices);
  void Draw();
  void Move();
};

class Renderer2D {
private:
  GLuint VAO, VBO, EBO, program;
  GLint u_model;
  Window window;

public:
  Renderer2D(Window &window);

  std::unordered_map<std::string, Object> Objects;
  std::function<void()> PreRenderStep = [](){};
  void RenderStep();
  void Run();

  void Create(std::string name, std::vector<float> &vertices, std::vector<uint32_t> &indices);
};

}
