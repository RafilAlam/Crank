#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

std::vector<float> vertices = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.5f,  0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f,
};

std::vector<uint32_t> indices = {
  0, 1, 2,
  2, 3, 0
};

int frames{0};

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);
  Object& rect1 = Renderer.Create("Rectangle1", vertices, indices);
  Object& rect2 = Renderer.Create("Rectangle2", vertices, indices);

  rect1.transform.position = glm::vec3(-0.5f,  0.5f, 0.0f);
  rect1.transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
  rect2.transform.position = glm::vec3( 0.5f, -0.5f, 0.0f);
  rect2.transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);

  Window.Keybind(GLFW_KEY_E, []() { std::cout << "KEY 'E' PRESSED!" << std::endl; });

  Renderer.PreRenderStep = [&]() {
    rect1.transform.rotation.z += 0.01;
    rect2.transform.rotation.z -= 0.01;
  };

  Renderer.Run();
  return 0;
}
