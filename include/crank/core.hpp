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
  const char* fetchShader(std::string fileName) {
    std::ifstream file(fileName);
    if (!file)
      std::cerr << "FAILED TO LOAD SHADER: " << fileName;
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
      content += line;
    }
    const char* ccontent = content.c_str();

    return ccontent;
  }
public:
  const GLuint handle;
  Shader(std::string fileName, GLenum shaderType);
};

class ShaderProgram {
private:
public:
  const GLuint handle;
  ShaderProgram();
  void AttachShader(Shader shader);
  void Link();
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
  unsigned long long baseVertex;
  Object(std::vector<float> &p_vertices, std::vector<unsigned int> &p_indices);
  void Draw();
};

class Buffer {
private:
public:
  GLenum type;
  GLuint handle;
  Buffer(GLenum bufferType, std::vector<Object> initialObjects);
  void Bind();
  void Data(std::vector<float> &data);
  void Data(std::vector<unsigned int> &data);
};

class VBO {
private:
public:
  Buffer buffer;
  VBO(std::vector<Object> objectstospawn);
};

class EBO {
private:
public:
  Buffer buffer;
  EBO(std::vector<Object> objectospawn);
};

}
