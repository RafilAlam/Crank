#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);
  Object& rectangle = Renderer.Create("Rectangle", Mesh::Rectangle(100, 100));
  Object& triangle = Renderer.Create("Triangle", Mesh::Triangle(100, 100));
  Object& circle = Renderer.Create("Circle", Mesh::Rectangle(100, 100));
 
  circle.color = glm::vec3(0.5f, 0.1f, 0.1f);
  circle.roundness = 1.0f;

  rectangle.color = glm::vec3(0.1f, 0.5f, 0.1f);
  rectangle.roundness = 0.5f;

  triangle.color = glm::vec3(0.1f, 0.1f, 0.5f);
  triangle.roundness = 1.0f;

  circle.transform.position = glm::vec3(600.0f, 200.0f, 0.0f);
  rectangle.transform.position = glm::vec3(400.0f, 200.0f, 0.0f);
  triangle.transform.position = glm::vec3(200.0f, 200.0f, 0.0f);

  Window.Keybind(GLFW_KEY_E, []() { std::cout << "KEY 'E' PRESSED!" << std::endl; });

  Renderer.PreRenderStep = [&]() {
//   rectangle.transform.rotation.z += 0.1;
  };

  Renderer.Run();
  return 0;
}
