#include <iostream>
#include <vector>

#include <crank/core.hpp>

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
  crank::Window Window("Crank", 800, 600);
  crank::Renderer2D Renderer(Window);
  Renderer.Create("Rectangle", vertices, indices);

  Renderer.PreRenderStep = []() {
    ++frames;
    std::cout << '\r' << "FRAME COUNT: " << frames << std::flush;
  };

  Renderer.Run();
  return 0;
}
