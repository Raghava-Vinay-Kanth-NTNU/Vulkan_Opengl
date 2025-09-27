#include "Vulkan_renderer.h"

Vulkan_renderer::Vulkan_renderer()
{
}

int Vulkan_renderer::init(GLFWwindow* newWindow)
{

	window = newWindow;
	try {
		createInstance();
	}
	catch (const std::runtime_error& e) {
		printf("error message: %s\n", e.what());
		return EXIT_FAILURE;
	}
	return 0;
}

void Vulkan_renderer::cleanup()
{

	vkDestroyInstance(instance, nullptr);

}

Vulkan_renderer::~Vulkan_renderer()
{
}

void Vulkan_renderer::createInstance()
{
	// creating info for vulkan instance
	VkInstanceCreateInfo createInfo = {};
	
	// 
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan App";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.apiVersion = VK_API_VERSION_1_4;

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	
	std::vector<const char*> instanceExtensions = std::vector<const char*>();
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (size_t i = 0; i < glfwExtensionCount; i++)
	{
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
	createInfo.ppEnabledExtensionNames = instanceExtensions.data();

	// later need to setup validation layers
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
	//create instance
	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

	if (result!= VK_SUCCESS)
	{
		throw std::runtime_error("failed to create a vulkan instance");
	}
}

bool Vulkan_renderer::checkInstanceExtensionSupport(std::vector<const char*>* checkExtensions)
{
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	// 1. Enumerate physical devices
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("Failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	// 2. Pick the first suitable device (for now, just take the first one)
	physicalDevice = devices[0];

	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensions.data());
	//check if names are available
	for (const auto &checkExtension : *checkExtensions) {
		
		bool hasExtension = false;
		//
		for (const auto& extension : extensions)
		{
			if (strcmp(checkExtension, extension.extensionName))
			{
				hasExtension = true;
				break;
			}

		}

		if (!hasExtension)
		{
			return false;
		}

	}
	return true;
}
