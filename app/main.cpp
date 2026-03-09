#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);

  Object& circle = Renderer.Create("Circle", Mesh::Rectangle(100, 100));
 
  circle.bgcolor = glm::vec4(0.5f, 0.1f, 0.1f, 1.0f);
  circle.borderwidth = 1.0f;
  circle.bordercolor = glm::vec3(1.0f);
  circle.roundness = 1.0f;

  Window.Keybind(GLFW_KEY_F, [&]() {
      printf("ResX: %f, ResY: %f\r", Window.resolution.x, Window.resolution.y);
      fflush(stdout);
  });

  Renderer.PreRenderStep = [&]() {
    circle.transform.position = glm::vec3(Window.resolution.x*0.5f, Window.resolution.y*0.5f, 0.0f);
  };

  Renderer.Run();
  return 0;
}
