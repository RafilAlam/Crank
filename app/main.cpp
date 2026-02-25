#include <iostream>
#include <vector>

#include <crank/core.hpp>

std::vector<float> vertices1 = {
   0.2f, -0.2f, 0.0f,
   0.4f, -0.2f, 0.0f,
   0.4f,  0.2f, 0.0f,
   0.2f,  0.2f, 0.0f,
};

std::vector<float> vertices2 = {
  -0.4f, -0.2f, 0.0f,
  -0.2f, -0.2f, 0.0f,
  -0.2f,  0.2f, 0.0f,
  -0.4f,  0.2f, 0.0f,
};

std::vector<uint32_t> indices = {
  0, 1, 2,
  2, 3, 0
};

int frames{0};

int main() {
  crank::Window Window("Crank", 800, 600);
  crank::Renderer2D Renderer(Window);
  Renderer.Create("Rectangle1", vertices1, indices);
  Renderer.Create("Rectangle2", vertices2, indices);

  Renderer.PreRenderStep = []() {
    ++frames;
    std::cout << '\r' << "FRAME COUNT: " << frames << std::flush;
  };

  Renderer.Run();
  return 0;
}
