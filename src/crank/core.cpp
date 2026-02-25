#include <crank/core.hpp>

std::string load_file_content(const std::string &fileName) {
  std::ifstream file(fileName);
  if (!file) {
    std::cout << "FAILED TO FETCH " << fileName << " FILE CONTENTS" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string line{}, content{};
  while (std::getline(file, line)) {
    content += line + '\n';
  }

  return content;
}

void debug_shader(std::string shaderName, GLuint shader) {
  GLint shader_compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
  if (!shader_compiled) {
    GLchar InfoLog[512];
    glGetShaderInfoLog(shader, 512, NULL, InfoLog);
    std::cout << "SHADER COMPILATION ERROR(" + shaderName + "):\n" + InfoLog << std::endl;
  }
}

void debug_program(std::string programName, GLuint program) {
  GLint program_linked;
  glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
  if (!program_linked) {
    GLchar InfoLog[512];
    glGetProgramInfoLog(program, 512, NULL, InfoLog);
    std::cout << "PROGRAM LINKING ERROR(" + programName + "):\n" + InfoLog << std::endl;
  }
}

namespace crank {

void error(std::string msg) {
  std::cout << "CRANK | ERROR: " + msg << std::endl;
  std::exit(EXIT_FAILURE);
}

Window::Window(std::string name, int p_width, int p_height): width(p_width), height(p_height) {
  if (!glfwInit()) error("GLFW INITIALISATION FAILED!");
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  handle = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
  if (!handle) {
    glfwTerminate();
    error("WINDOW CREATION FAILED!");
  }
  glfwMakeContextCurrent(handle);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    error("FAILED TO START GLAD!");
  }
  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* window, int f_width, int f_height) {
    glViewport(0, 0, f_width, f_height);
  });
}

Object::Object(std::vector<float> &p_vertices, std::vector<uint32_t> &p_indices): vertices(p_vertices), indices(p_indices) {};
void Object::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL); 
}

Renderer2D::Renderer2D(Window &window): window(window) {

  std::string s_vshader = load_file_content("./shaders/vertex.glsl");
  std::string s_fshader = load_file_content("./shaders/fragment.glsl");

  const char* c_vshader = s_vshader.c_str();
  const char* c_fshader = s_fshader.c_str();

  std::cout << "Loaded Vertex Shader:\n" << c_vshader << "\nLoaded Fragment Shader:\n" << c_fshader << std::endl;

  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &c_vshader, NULL);
  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &c_fshader, NULL);
  glCompileShader(vertexshader);
  glCompileShader(fragmentshader);

  debug_shader("VERTEX", vertexshader);
  debug_shader("FRAGMENT", fragmentshader);

  program = glCreateProgram();
  glAttachShader(program, vertexshader);
  glAttachShader(program, fragmentshader);
  glLinkProgram(program);

  debug_program("PROGRAM", program);
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);

  u_model = glGetUniformLocation(program, "u_model");
}

void Renderer2D::RenderStep() {
  glUseProgram(program);
  for (auto &pair : Objects) {
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(pair.second.transform.GetMatrix()));
    pair.second.Draw();
  }
}

void Renderer2D::Run() {
  while(!glfwWindowShouldClose(window.handle)) {
    glClear(GL_COLOR_BUFFER_BIT);

    PreRenderStep();
    RenderStep();

    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }
  glfwTerminate();
}

void Renderer2D::Create(std::string name, std::vector<float> &vertices, std::vector<uint32_t> &indices) {
  auto[it, inserted] = Objects.try_emplace(std::move(name), vertices, indices);
  Object &obj = it->second;

  glCreateBuffers(1, &obj.VBO);
  glNamedBufferStorage(obj.VBO, sizeof(float)*vertices.size(), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &obj.EBO);
  glNamedBufferStorage(obj.EBO, sizeof(uint32_t)*indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &obj.VAO);
  glVertexArrayVertexBuffer(obj.VAO, 0, obj.VBO, 0, 3*sizeof(float));
  glVertexArrayElementBuffer(obj.VAO, obj.EBO);
  glEnableVertexArrayAttrib(obj.VAO, 0);
  glVertexArrayAttribFormat(obj.VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(obj.VAO, 0, 0);
}

}
