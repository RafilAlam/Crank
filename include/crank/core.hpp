#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>
#include <unordered_map>
#include <utility>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

std::string load_file_content(const std::string &fileName);
void debug_shader(std::string shaderName, GLuint shader);
void debug_program(std::string programName, GLuint program);

namespace crank {

void error(std::string msg);

struct WindowData;

class Window {
private:
  std::unordered_map<int, std::function<void()>> keybinds;
public:
  GLFWwindow* handle;
  WindowData* dataptr;
  Window(std::string name, int width, int height);
  void Keybind(int key, std::function<void()> callback); // key is GLFW key tokens
  glm::vec2 getResolution();
};

enum MESH_TYPE {
  M_MODEL,
  M_RECT,
  M_TRI,
  M_CIR
};

class Mesh {
private:
  std::vector<float> vertices;
  std::vector<uint32_t> indices;
  Mesh(std::vector<float> &p_vertices, std::vector<uint32_t> &p_indices, MESH_TYPE p_type, glm::vec2 p_size);
public:
  MESH_TYPE type;
  glm::vec2 size;
  float* getVertices();
  uint32_t* getIndices();
  size_t numVertices();
  size_t numIndices();
  static Mesh Raw(std::vector<float> p_vertices, std::vector<uint32_t> p_indices);
  static Mesh Rectangle(float width, float height);
  static Mesh Triangle(float base, float height);
  static Mesh Circle(float radius);
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
  Transform transform;
  glm::vec3 color = glm::vec3(1.0f);
  Mesh mesh;

  Object(Mesh &&p_mesh);
  void Draw();
};

class Renderer2D {
private:
  GLuint VAO, VBO, EBO, program;
  GLint u_projection, u_model;
  GLint u_modelposition, u_color, u_meshtype, u_resolution, u_circleradius;
public:
  Window window;
  Renderer2D(Window &window);

  std::unordered_map<std::string, Object> Objects;
  std::function<void()> PreRenderStep = [](){};
  void RenderStep();
  void Run();

  Object& Create(std::string name, Mesh p_mesh);
};

struct WindowData {
  Window* window;
  Renderer2D* renderer;
};

}
