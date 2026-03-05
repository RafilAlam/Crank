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

Window::Window(std::string name, int width, int height) {
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
  
  dataptr = new WindowData{this, NULL};
  glfwSetWindowUserPointer(handle, dataptr);
  glfwSetKeyCallback(handle, [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
    WindowData* dataptr = static_cast<WindowData*>(glfwGetWindowUserPointer(handle));
    if (action == GLFW_PRESS and dataptr->window->keybinds.count(key) > 0) {
      dataptr->window->keybinds.at(key)();
    }
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    error("FAILED TO START GLAD!");
  }
  glViewport(0, 0, width, height);
}
void Window::Keybind(int key, std::function<void()> callback) {
  keybinds.insert_or_assign(key, callback);
}
glm::vec2 Window::getResolution() {
  int w, h;
  if (!handle) error("WINDOW MISSING!");
  glfwGetFramebufferSize(handle, &w, &h);
  return glm::vec2(w, h);
}

Mesh::Mesh(std::vector<float> &p_vertices, std::vector<uint32_t> &p_indices, MESH_TYPE p_type, glm::vec2 p_size): vertices(p_vertices), indices(p_indices), type(p_type), size(p_size) {}
float* Mesh::getVertices() { return vertices.data(); }
uint32_t* Mesh::getIndices() { return indices.data(); }
size_t Mesh::numVertices() { return vertices.size(); }
size_t Mesh::numIndices() { return indices.size(); }
Mesh Mesh::Raw(std::vector<float> p_vertices, std::vector<uint32_t> p_indices) {
  return Mesh(p_vertices, p_indices, M_MODEL, glm::vec2(0.0f));
}
Mesh Mesh::Rectangle(float width, float height) {
  float x = width/2;
  float y = height/2;
  std::vector<float> vertices = {
    -x, -y, 0.0f,
     x, -y, 0.0f,
     x,  y, 0.0f,
    -x,  y, 0.0f,
  };

  std::vector<uint32_t> indices = {
    0, 1, 2,
    2, 3, 0,
  };

  return Mesh(vertices, indices, M_RECT, glm::vec2(width, height));
}
Mesh Mesh::Triangle(float base, float height) {
  float x = base/2;
  float y = height/2;
  std::vector<float> vertices = {
    -x, -y, 0.0f,
     x, -y, 0.0f,
     0,  y, 0.0f,
  };
  std::vector<uint32_t> indices = {
    0, 1, 2
  };

  return Mesh(vertices, indices, M_TRI, glm::vec2(base, height));
}
Mesh Mesh::Circle(float radius) {
  float x = radius;
  float y = radius;
  std::vector<float> vertices = {
    -x, -y, 0.0f,
     x, -y, 0.0f,
     x,  y, 0.0f,
    -x,  y, 0.0f,
  };

  std::vector<uint32_t> indices = {
    0, 1, 2,
    2, 3, 0,
  };

  return Mesh(vertices, indices, M_CIR, glm::vec2(radius));
}

Object::Object(Mesh &&p_mesh): mesh(p_mesh) {};
void Object::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, mesh.numIndices(), GL_UNSIGNED_INT, NULL); 
}

Renderer2D::Renderer2D(Window &window): window(window) {

  std::string s_vshader = load_file_content("./shaders/vertex.glsl");
  std::string s_fshader = load_file_content("./shaders/fragment.glsl");

  const char* c_vshader = s_vshader.c_str();
  const char* c_fshader = s_fshader.c_str();

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
  glUseProgram(program);

  u_projection = glGetUniformLocation(program, "u_projection");
  u_model = glGetUniformLocation(program, "u_model");
  u_modelposition = glGetUniformLocation(program, "u_modelposition");
  u_modelsize = glGetUniformLocation(program, "u_modelsize");
  u_cornerradius = glGetUniformLocation(program, "u_cornerradius");
  u_color = glGetUniformLocation(program, "u_color");
  u_meshtype = glGetUniformLocation(program, "u_meshtype");
  u_resolution = glGetUniformLocation(program, "u_resolution");
  u_circleradius = glGetUniformLocation(program, "u_circleradius");
  
  glm::vec2 res = window.getResolution();
  glm::mat4 projection = glm::ortho(0.0f, (float)res.x, 0.0f, (float)res.y, -1.0f, 1.0f);
  glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  window.dataptr->renderer = this;

  glfwSetFramebufferSizeCallback(window.handle, [](GLFWwindow* window, int f_width, int f_height) {
    WindowData* dataptr = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, f_width, f_height);
    glm::vec2 res = dataptr->window->getResolution();
    glm::mat4 projection = glm::ortho(0.0f, (float)res.x, 0.0f, (float)res.y, -1.0f, 1.0f);
    glUniformMatrix4fv(dataptr->renderer->u_projection, 1, GL_FALSE, glm::value_ptr(projection));
  });
}

void Renderer2D::RenderStep() {
  glUseProgram(program);
  glEnable(GL_BLEND);
  for (auto &pair : Objects) {
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(pair.second.transform.GetMatrix()));
    glUniform2f(u_modelposition, pair.second.transform.position.x, pair.second.transform.position.y);
    glUniform2fv(u_modelsize, 1, glm::value_ptr(pair.second.mesh.size));
    glUniform1f(u_cornerradius, pair.second.cornerradius);
    glUniform3fv(u_color, 1, glm::value_ptr(pair.second.color));
    glUniform1i(u_meshtype, pair.second.mesh.type);
    glm::vec2 res = window.getResolution();
    glUniform2f(u_resolution, res.x, res.y);
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

Object& Renderer2D::Create(std::string name, Mesh p_mesh) {
  auto&& [it, inserted] = Objects.try_emplace(std::move(name), std::move(p_mesh));
  Object &obj = it->second;

  glCreateBuffers(1, &obj.VBO);
  glNamedBufferStorage(obj.VBO, sizeof(float)*obj.mesh.numVertices(), obj.mesh.getVertices(), GL_DYNAMIC_STORAGE_BIT);

  glCreateBuffers(1, &obj.EBO);
  glNamedBufferStorage(obj.EBO, sizeof(uint32_t)*obj.mesh.numIndices(), obj.mesh.getIndices(), GL_DYNAMIC_STORAGE_BIT);

  glCreateVertexArrays(1, &obj.VAO);
  glVertexArrayVertexBuffer(obj.VAO, 0, obj.VBO, 0, 3*sizeof(float));
  glVertexArrayElementBuffer(obj.VAO, obj.EBO);
  glEnableVertexArrayAttrib(obj.VAO, 0);
  glVertexArrayAttribFormat(obj.VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(obj.VAO, 0, 0);

  return obj;
}

}
