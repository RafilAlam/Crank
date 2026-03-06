#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);
  Object& rectangle = Renderer.Create("Rectangle", Mesh::Rectangle(100, 100));
 
  rectangle.color = glm::vec3(0.5f, 0.1f, 0.1f);
  rectangle.cornerradius = 10.0f;

  rectangle.transform.position = glm::vec3(500.0f, 200.0f, 0.0f);

  Window.Keybind(GLFW_KEY_E, []() { std::cout << "KEY 'E' PRESSED!" << std::endl; });

  Renderer.PreRenderStep = [&]() {
//    rectangle.transform.rotation.z += 0.1;
  };

  Renderer.Run();
  return 0;
}
