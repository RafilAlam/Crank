#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

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
  Shader(std::string fileName): handle(glCreateShader());
}

class ShaderProgram {
private:
public:
  const GLuint handle;
  ShaderProgram();
  AttachShader();
  Link();
}

class Window {
private:
public:
  Window();
}

class RenderingPipeline {
private:
public:
  
}

}
