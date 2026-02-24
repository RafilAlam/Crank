#include <iostream>
#include <vector>
#include <cmath>

#include <crank/core.hpp>

std::vector<float> vertices = {
  -0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
};

std::vector<uint32_t> indices = {
  0, 1, 2,
};

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "MyWindow", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to start GLAD" << std::endl;
      glfwTerminate();
      return -1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
      glViewport(0, 0, width, height); 
  });

  GLuint vao, vbo, ebo;
  glCreateBuffers(1, &vbo);
  glNamedBufferStorage(vbo, sizeof(float)*vertices.size(), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &ebo);
  glNamedBufferStorage(ebo, sizeof(uint32_t)*indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &vao);
  glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3*sizeof(float));
  glVertexArrayElementBuffer(vao, ebo);
  glEnableVertexArrayAttrib(vao, 0);
  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);

  std::string s_vshader = load_file_content("./shaders/vertex.glsl");
  std::string s_fshader = load_file_content("./shaders/fragment.glsl");

  const char* c_vshader = s_vshader.c_str();
  const char* c_fshader = s_fshader.c_str();

  std::cout << "Loaded Vertex Shader:\n" << c_vshader << "\nLoaded Fragment Shader:\n" << c_fshader << std::endl;

  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &c_vshader, NULL);
  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &c_fshader, NULL);
  glCompileShader(vertexshader);
  glCompileShader(fragmentshader);

  debug_shader("VERTEX", vertexshader);
  debug_shader("FRAGMENT", fragmentshader);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexshader);
  glAttachShader(program, fragmentshader);
  glLinkProgram(program);

  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
};
