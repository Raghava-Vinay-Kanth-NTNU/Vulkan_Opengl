#define GLFW_INCLUDE_VULKAN 

#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>

int main(){

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "test_window", nullptr, nullptr);
	uint32_t ext = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &ext, nullptr);
	printf("extension count: %i", ext);
	glm::mat4 testMat(1.0f);
	glm::vec4 testVec(1.0f);

	auto testRes = testMat * testVec;
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}


