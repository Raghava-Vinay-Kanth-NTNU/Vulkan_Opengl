#pragma once
#define GLFW_INCLUDE_VULKAN 

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>


class Vulkan_renderer
{

public:
	Vulkan_renderer();

	int init(GLFWwindow* newWindow);
	void cleanup();
	~Vulkan_renderer();

private:

	GLFWwindow* window;

	//vulkan componenets

	VkInstance instance;

	void createInstance();

	//support functions

	bool checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions);

};

