#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint initVertexArray(std::vector<GLfloat> *vertices)
{
	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(GLfloat), vertices->data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return VAO;
}

GLuint initElementArray(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);						// Posiiton
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));	// Color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));	// Texture Coords
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

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

GLuint loadTexture(const char* fileName, GLenum textureUnit)
{
	GLint width, height, nrChannels;
	GLubyte* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Failed to load Texture Image" << std::endl;
		glfwTerminate();
		return -1;
	}
	GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	return texture;
}