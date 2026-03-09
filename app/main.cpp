#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

class Planet {
private:
  Window* window;
  Renderer2D* renderer;
  Object* body;
  Object* moon;
  float angle {0.0f};
public:
  Planet(Window& p_window, Renderer2D& p_renderer)
  : window(&p_window),
    renderer(&p_renderer),
    body(&renderer->Create("Planet", Mesh::Rectangle(100, 100))),
    moon(&renderer->Create("Moon", Mesh::Rectangle(50, 50)))
  {
    body->bgcolor = glm::vec4(0.5f, 0.1f, 0.1f, 1.0f);
    body->borderwidth = 1.0f;
    body->bordercolor = glm::vec3(1.0f);
    body->roundness = 1.0f;
    body->transform.scale = glm::vec3(3.0f, 3.0f, 0.0f);

    moon->bgcolor = glm::vec4(0.1f, 0.1f, 0.5f, 1.0f);
    moon->borderwidth = 1.0f;
    moon->bordercolor = glm::vec3(1.0f);
    moon->roundness = 1.0f;
    moon->transform.scale = glm::vec3(3.0f, 3.0f, 0.0f);
  }

  void update() {
    body->transform.position = glm::vec3(window->resolution.x*0.5f, window->resolution.y*0.5f, 0.0f);
    float sinv = sin(angle);
    float cosv = cos(angle);
    moon->transform.position = glm::vec3(body->transform.position.x+300*sinv, body->transform.position.y, 0.03f*cosv);
    moon->transform.scale = glm::vec3(cosv+2.0f, cosv+2.0f, 0.0f);
    angle+=0.01f;
  }
};

int main() {
  Window Window("Crank", 800, 600);
  Renderer2D Renderer(Window);

  Window.Keybind(GLFW_KEY_F, [&]() {
      printf("ResX: %f, ResY: %f\r", Window.resolution.x, Window.resolution.y);
      fflush(stdout);
  });

  Planet planet(Window, Renderer);

  Renderer.PreRenderStep = [&]() {
    planet.update();
  };

  Renderer.Run();
  return 0;
}
