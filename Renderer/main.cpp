#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string vShaderSource = R"(
#version 460

in vec3 aPos;

void main() 
{
	gl_Position = vec4(aPos, 1.0f);
}
)";

std::string fShaderSource = R"(
#version 460

out vec4 FragColor;

void main() 
{
	FragColor = vec4(0.57f, 0.32f, 0.27f, 1.0f);
}
)";

void initShaders(void)
{
	GLuint program = glCreateProgram();

	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsrc = vShaderSource.c_str();
	const char* fsrc = fShaderSource.c_str();

	glShaderSource(vshader, 1, &vsrc, NULL);
	glShaderSource(fshader, 1, &fsrc, NULL);

	glCompileShader(vshader);
	glCompileShader(fshader);

	glAttachShader(program, vshader);
	glAttachShader(program, fshader);

	glLinkProgram(program);
	glUseProgram(program);

	glDeleteShader(vshader);
	glDeleteShader(fshader);
}

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

	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	initShaders();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.02f, 0.07f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	std::cout << "GLFW Window Closed!" << std::endl;
	glfwTerminate();
	return 0;
}