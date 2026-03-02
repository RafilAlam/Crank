#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int frames{0};

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);
  Object& circle = Renderer.Create("Circle1", Mesh::Circle(100));
  circle.color = glm::vec3(0.5f, 0.2f, 0.2f);
  Object& triangle = Renderer.Create("Triangle2", Mesh::Triangle(100, 100));
  triangle.color = glm::vec3(0.2f, 0.5f, 0.2f);

  circle.transform.position = glm::vec3(500.0f, 200.0f, 0.0f);
  //circle.transform.scale = glm::vec3(100.0f, 100.0f, 1.0f);
  triangle.transform.position = glm::vec3(200.0f, 200.0f, 0.0f);
  //triangle.transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);

  Window.Keybind(GLFW_KEY_E, []() { std::cout << "KEY 'E' PRESSED!" << std::endl; });

  Renderer.PreRenderStep = [&]() {
    circle.transform.rotation.z += 0.1;
    triangle.transform.rotation.z -= 0.1;
  };

  Renderer.Run();
  return 0;
}
