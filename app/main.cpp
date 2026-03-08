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
 
  circle.bgcolor = glm::vec4(0.5f, 0.1f, 0.1f, 1.0f);
  circle.borderwidth = 10.0f;
  circle.bordercolor = glm::vec3(1.0f);
  circle.roundness = 1.0f;

  rectangle.bgcolor = glm::vec4(0.1f, 0.5f, 0.1f, 1.0f);
  rectangle.borderwidth = 10.0f;
  rectangle.bordercolor = glm::vec3(1.0f);
  rectangle.roundness = 0.5f;

  triangle.bgcolor = glm::vec4(0.1f, 0.1f, 0.5f, 1.0f);
  triangle.borderwidth = 10.0f;
  triangle.bordercolor = glm::vec3(1.0f);
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
