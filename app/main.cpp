#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int frames{0};

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);
  Object& circle = Renderer.Create("Circle1", Mesh::Circle(100));
  Object& triangle = Renderer.Create("Triangle2", Mesh::Triangle(100, 100));

  circle.transform.position = glm::vec3(50.0f,  80.0f, 0.0f);
  //circle.transform.scale = glm::vec3(100.0f, 100.0f, 1.0f);
  triangle.transform.position = glm::vec3( 100.0f, 200.0f, 0.0f);
  //triangle.transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);

  Window.Keybind(GLFW_KEY_E, []() { std::cout << "KEY 'E' PRESSED!" << std::endl; });

  Renderer.PreRenderStep = [&]() {
    circle.transform.rotation.z += 0.1;
    triangle.transform.rotation.z -= 0.1;
  };

  Renderer.Run();
  return 0;
}
