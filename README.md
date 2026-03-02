<h1 align="center"> Crank - C++ Graphics Engine </h1>
<p><strong>Crank</strong> is an OpenGL Graphics Engine written in the C++ language.
It can be used to quickly write cross-platform C++ applications including not just games, 
but simulations, graph visualisations and tech showcases. </p>

<h2> Installation: </h2>
<p> Crank uses CMake as its build system. </p>

```bash
cd path/to/crank/directory

mkdir build

cd build

cmake ..

cd ..

cmake --build build
```
</code>
</pre>
<p>Application code can be found in the app directory.</p>

<h2>Example Crank App</h2>
<p>The code below is a basic example of an application that shows a spinning square, triangle and a circle.</p>
```cpp
#include <iostream>
#include <vector>

#include <crank/core.hpp>
using namespace crank;

int frames{0};

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
```
