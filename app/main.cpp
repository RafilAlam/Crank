#include <iostream>
#include <vector>
#include <cmath>

#include <crank/core.hpp>

std::vector<float> vertices = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

std::vector<unsigned int> indices = {
  0, 1, 2,
};

int main() {
  crank::Window window("Crank", 800, 600);

  std::vector<crank::Object> objects;
  objects.emplace_back(vertices, indices);

  crank::Shader vertexShader("vertex.glsl", GL_VERTEX_SHADER);
  crank::Shader fragmentShader("fragment.glsl", GL_FRAGMENT_SHADER);

  crank::ShaderProgram shaderProgram;
  shaderProgram.AttachShader(vertexShader);
  shaderProgram.AttachShader(fragmentShader);
  shaderProgram.Link();
  shaderProgram.Use();
  vertexShader.Delete();
  fragmentShader.Delete();

  crank::IndexedRenderer renderer(objects);
  renderer.VAO.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
  std::cout << "Engine Loaded!" << std::endl;

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  while (!glfwWindowShouldClose(window.handle)) {
    glClear(GL_COLOR_BUFFER_BIT);

    float green = 0.5*sin(glfwGetTime())+0.5;
    shaderProgram.SetUniform4f("outColor", 0.0f, green, 0.0f, 1.0f);
    for (auto& obj : objects) {
      obj.Draw();
    }

    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}
