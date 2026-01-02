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

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
	};

	std::vector<GLuint> indices = {
		0, 3, 2,
		0, 1, 2
	};

	GLuint VAO = initVertexArray(vertices);
	GLuint ProgramOrange = initShaders(fetchShader("tutorial.vert"), fetchShader("tutorial.frag"));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.02f, 0.07f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(ProgramOrange);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "GLFW Window Closed!" << std::endl;
	glfwTerminate();
	return 0;
}