#include <crank/core.hpp>

namespace crank {

Shader::Shader(std::string fileName, GLenum shaderType): handle(glCreateShader(shaderType)) {
  std::string shadercontent = fetchShader(fileName);
  const char* c_shadercontent = shadercontent.c_str();
  glShaderSource(handle, 1, &c_shadercontent, NULL);
  glCompileShader(handle);
  Debug(fileName);
}
void Shader::Debug(std::string name) {
  int success;
  char infoLog[512];
  glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(handle, 512, NULL, infoLog);
    std::cout << name + " SHADER COMPILATION FAILED!\n" << infoLog << std::endl;
  }
}
void Shader::Delete() {
  glDeleteShader(handle);
}

ShaderProgram::ShaderProgram(): handle(glCreateProgram()) {}
void ShaderProgram::Debug() {
  int success;
  char infoLog[512];
  glGetProgramiv(handle, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(handle, 512, NULL, infoLog);
    std::cout << "PROGRAM LINKING FAILED!\n" << infoLog << std::endl;
  }
}
void ShaderProgram::AttachShader(Shader &shader) {
  glAttachShader(handle, shader.handle);
}
void ShaderProgram::Link() {
  glLinkProgram(handle);
  Debug();
}
void ShaderProgram::Use() {
  glUseProgram(handle);
}
void ShaderProgram::SetUniform4f(std::string name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(handle, name.c_str()), x, y, z, w);
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
void VertexArrayObject::SetAttribute(unsigned int attributeIndex, unsigned int n_components, GLenum dataType, GLboolean normalized, GLsizei stride, unsigned long long offset) {
  glVertexAttribPointer(attributeIndex, n_components, dataType, normalized, stride, (void*)offset);
  glEnableVertexAttribArray(attributeIndex);
}

VertexBufferObject::VertexBufferObject(std::vector<Object> &objectstospawn): buffer(GL_ARRAY_BUFFER, objectstospawn) {
  std::vector<float> totalvertices;
  unsigned int vertexcount{0};
  for (auto &obj : objectstospawn) {
    obj.baseVertex = vertexcount;
    vertexcount += obj.indices.size();
    std::cout << obj.baseVertex << std::endl;
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

IndexedRenderer::IndexedRenderer(std::vector<Object> &objectstospawn): VAO(), VBO(objectstospawn), EBO(objectstospawn) {}
  
Object::Object(std::vector<float> &p_vertices, std::vector<unsigned int> &p_indices): vertices(std::move(p_vertices)), indices(std::move(p_indices)) {};
void Object::Draw() {
  glDrawElementsBaseVertex(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)offsetIndices, baseVertex);
}

}
