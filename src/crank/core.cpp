#include <crank/core.hpp>

namespace crank {

Shader::Shader(std::string fileName, GLenum shaderType): handle(glCreateShader(shaderType)) {
  const char* shadercontent = fetchShader(fileName);
  glShaderSource(handle, 1, &shadercontent, NULL);
  glCompileShader(handle);
}
void Shader::Delete() {
  glDeleteShader(handle);
}

ShaderProgram::ShaderProgram(): handle(glCreateProgram()) {}
void ShaderProgram::AttachShader(Shader &shader) {
  glAttachShader(handle, shader.handle);
}
void ShaderProgram::Link() {
  glLinkProgram(handle);
}
void ShaderProgram::Use() {
  glUseProgram(handle);
}

Window::Window(std::string name, int height, int width) {
  if (!glfwInit()) {
    std::cerr << "GLFW couldn't start" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  handle = glfwCreateWindow(height, width, name.c_str(), NULL, NULL);
  if (!handle) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(handle);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to inititalise GLAD" << std::endl;
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glViewport(0, 0, height, width);
  glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });
}

Buffer::Buffer(GLenum bufferType, std::vector<Object> &initialObjects): type(bufferType) {
  glGenBuffers(1, &handle);
}
void Buffer::Bind() {
  glBindBuffer(type, handle);
}
void Buffer::Data(std::vector<float> &data) {
  glBufferData(type, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
}
void Buffer::Data(std::vector<unsigned int> &data) {
  glBufferData(type, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);
}

VertexArrayObject::VertexArrayObject() {
  glGenVertexArrays(1, &handle);
  glBindVertexArray(handle);
}
void VertexArrayObject::Bind() {
  glBindVertexArray(handle);
}

VertexBufferObject::VertexBufferObject(std::vector<Object> &objectstospawn): buffer(GL_ARRAY_BUFFER, objectstospawn) {
  std::vector<float> totalvertices;
  for (auto &obj : objectstospawn) {
    obj.baseVertex = totalvertices.size()/3;
    totalvertices.insert(totalvertices.end(), obj.vertices.begin(), obj.vertices.end());
  }
  buffer.Bind();
  buffer.Data(totalvertices);
}

ElementBufferObject::ElementBufferObject(std::vector<Object> &objectstospawn): buffer(GL_ELEMENT_ARRAY_BUFFER, objectstospawn) {
  std::vector<unsigned int> totalindices;
  for (auto &obj : objectstospawn) {
    obj.offsetIndices = totalindices.size() * sizeof(unsigned int);
    totalindices.insert(totalindices.end(), obj.indices.begin(), obj.indices.end());
  }
  buffer.Bind();
  buffer.Data(totalindices);
}

IndexedRenderer::IndexedRenderer(std::vector<Object> &objectstospawn): VAO(), VBO(objectstospawn), EBO(objectstospawn) {
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}
  
Object::Object(std::vector<float> &p_vertices, std::vector<unsigned int> &p_indices): vertices(std::move(p_vertices)), indices(std::move(p_indices)) {};
void Object::Draw() {
  std::cout << offsetIndices << " " << baseVertex << indices.size() << std::endl;
  glDrawElementsBaseVertex(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)offsetIndices, baseVertex);
}

}
