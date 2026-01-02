#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint initVertexArray(std::vector<GLfloat> vertices)
{
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return VAO;
}

GLuint initElementArray(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
{
	GLuint VAO, EBO, VBO;

	glGenVertexArrays(1, &VAO);;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return VAO;
}

GLuint initShaders(std::string vShaderSource, std::string fShaderSource)
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

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	return program;
}