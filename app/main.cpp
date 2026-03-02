#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);
  Object& rectangle = Renderer.Create("Rectangle", Mesh::Rectangle(100, 100));
  Object& triangle = Renderer.Create("", Mesh::Triangle(100, 100));
  Object& circle = Renderer.Create("Circle", Mesh::Circle(50));

  rectangle.color = glm::vec3(0.5f, 0.1f, 0.1f);
  triangle.color = glm::vec3(0.1f, 0.5f, 0.1f);
  circle.color = glm::vec3(0.1f, 0.1f, 0.5f);

  rectangle.transform.position = glm::vec3(200.0f, 200.0f, 0.0f);
  triangle.transform.position = glm::vec3(350.0f, 200.0f, 0.0f);
  circle.transform.position = glm::vec3(500.0f, 200.0f, 0.0f);

  Window.Keybind(GLFW_KEY_E, []() { std::cout << "KEY 'E' PRESSED!" << std::endl; });

  Renderer.PreRenderStep = [&]() {
    rectangle.transform.rotation.z += 0.1;
    triangle.transform.rotation.z += 0.1;
    circle.transform.rotation.z += 0.1;
  };

  Renderer.Run();
  return 0;
}
