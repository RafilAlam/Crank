#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void)
{
	if (!glfwInit())
		std::cout << "GLFW Failed to initialise!" << std::endl;
}