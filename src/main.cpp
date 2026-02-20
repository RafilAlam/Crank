#include <iostream>
#include <vector>

#include <crank/core.hpp>

std::vector<float> vertices = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

std::vector<unsigned int> indices = {
  0, 1, 2,
};

int main() {
  crank::Window window("Crank", 800, 600);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  while (!glfwWindowShouldClose(window.handle)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
