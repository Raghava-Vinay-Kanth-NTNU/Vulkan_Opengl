#define GLFW_INCLUDE_VULKAN 

#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include "Vulkan_renderer.h"

GLFWwindow* window;

Vulkan_renderer vulkan_renderer;

void initWindow(std::string wName = "test_window", const int width = 800, const int height = 600)
{
	glfwInit();
	// use only vulkan
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}
int main(){

	initWindow("Test_window", 800, 600);

	//create vulkan renderer instance

	if (vulkan_renderer.init(window) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	vulkan_renderer.cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


