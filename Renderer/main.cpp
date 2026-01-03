#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GLfunctions.hpp"
#include "tools.hpp"

int main(void)
{
	if (!glfwInit())
	{
		std::cerr << "GLFW Failed to initialise!" << std::endl; 
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	stbi_set_flip_vertically_on_load(true);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Renderer", NULL, NULL);
	if (!window)
	{
		std::cerr << "GLFW Failed to create a window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD Failed to initialise!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	std::vector<GLfloat> vertices = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	std::vector<GLuint> indices = {
		0, 3, 2,
		2, 1, 0
	};

	GLuint VAO = initElementArray(vertices, indices);
	GLuint Program = initShaders(fetchShader("tutorial.vert"), fetchShader("tutorial.frag"));
	glUseProgram(Program);

	GLuint texture1 = loadTexture("container.jpg", GL_TEXTURE0);
	GLuint texture2 = loadTexture("awesomeface.png", GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(Program, "Texture1"), 0);
	glUniform1i(glGetUniformLocation(Program, "Texture2"), 1);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.02f, 0.07f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(Program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "GLFW Window Closed!" << std::endl;
	glfwTerminate();
	return 0;
}