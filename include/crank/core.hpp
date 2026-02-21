#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <functional>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace crank {

class Shader {
private:
  std::string fetchShader(std::string fileName) {
    std::ifstream file("./shaders/" + fileName);
    if (!file)
      std::cerr << "FAILED TO LOAD SHADER: " << fileName << std::endl;
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
      content += line + '\n';
    }

    return content;
  }
public:
  const GLuint handle;
  Shader(std::string fileName, GLenum shaderType);
  void Debug(std::string name);
  void Delete();
};

class ShaderProgram {
private:
public:
  const GLuint handle;
  ShaderProgram();
  void Debug();
  void AttachShader(Shader &shader);
  void Link();
  void Use();
  void SetUniform4f(std::string name, float x, float y, float z, float w);
};

class Window {
private:
public:
  GLFWwindow* handle;
  Window(std::string name, int height, int width);
};

class Object {
private:
public:
  std::vector<float> vertices;
  std::vector<unsigned int> indices;
  unsigned long long offsetIndices;
  GLint baseVertex;
  Object(std::vector<float> &p_vertices, std::vector<unsigned int> &p_indices);
  void Draw();
};

class Buffer {
private:
public:
  GLenum type;
  GLuint handle;
  Buffer(GLenum bufferType, std::vector<Object> &initialObjects);
  void Bind();
  void Data(std::vector<float> &data);
  void Data(std::vector<unsigned int> &data);
};

class VertexArrayObject {
private:
public:
  GLuint handle;
  VertexArrayObject();
  void Bind();
  void SetAttribute(unsigned int attributeIndex, unsigned int n_components, GLenum dataType, GLboolean normalized, GLsizei stride, unsigned long long offset);
};

class VertexBufferObject {
private:
public:
  Buffer buffer;
  VertexBufferObject(std::vector<Object> &objectstospawn);
};

class ElementBufferObject {
private:
public:
  Buffer buffer;
  ElementBufferObject(std::vector<Object> &objectstospawn);
};

class IndexedRenderer {
private:
public:
  VertexArrayObject VAO;
  VertexBufferObject VBO;
  ElementBufferObject EBO;
  IndexedRenderer(std::vector<Object> &objectstospawn);
};

}
