#include <iostream>
#include <GLFW/glfw3.h>

int main() {
  GLFWwindow* window;

  if (!glfwInit()) {
    std::cout << "GLFW couldn't start" << std::endl;
    return -1;
  }

  window = glfwCreateWindow(640, 480, "MyWindow", NULL, NULL);
  std::cout << "Worked without errors!\n";

  return 0;
}
