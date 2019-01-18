//
// Created by efarhan on 1/18/19.
//
#include <vector>
#include <stdexcept>
#include <iostream>
#include <hello_triangle.h>
#include <SDL_vulkan.h>
#include <vk_utils.h>

void HelloTriangleApplication::createSDLWindow()
{
  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  // Create an application window with the following settings:
  window = SDL_CreateWindow(
      "An SDL2 Vulkan window",                  // window title
      SDL_WINDOWPOS_UNDEFINED,           // initial x position
      SDL_WINDOWPOS_UNDEFINED,           // initial y position
      640,                               // width, in pixels
      480,                               // height, in pixels
      SDL_WINDOW_VULKAN                 // flags - see below
  );

  // Check that the window was successfully created
  if (window == NULL) {
      // In the case that the window could not be made...
      printf("Could not create window: %s\n", SDL_GetError());
      throw std::runtime_error("");
    }
}

void HelloTriangleApplication::createInstance()
{

  
  //Check the Vulkan extensionsS
  unsigned int count;
  if (!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr)) {
      throw std::runtime_error("Error while trying to get Vulkan instance extensions");
    }

  std::vector<const char*> extensions = {
      VK_EXT_DEBUG_REPORT_EXTENSION_NAME // Sample additional extension
  };
  size_t additional_extension_count = extensions.size();
  extensions.resize(additional_extension_count + count);

  if (!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data() + additional_extension_count)) {
      throw std::runtime_error("Error while trying to get additional Vulkan instance extensions");
    }

  for(auto& ext : extensions)
    {
      std::cout << "Extension: " << ext << "\n";
    }


  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "SAE Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  if (enableValidationLayers && !checkValidationLayerSupport()) {
	  throw std::runtime_error("validation layers requested, but not available!");
  }

  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  if (enableValidationLayers)
    {
      createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
      for(auto& validationLayer : validationLayers)
        {
          std::cout << "Validation layer: " << validationLayer << "\n";
        }
    }
  else
    {
      createInfo.enabledLayerCount = 0;
    }

  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if (result != VK_SUCCESS) {
      throw std::runtime_error("vkCreateInstace was not successful");
    }
  VkSurfaceKHR surface;
  if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
      throw std::runtime_error("Failed to create Vulkan surface");
    }
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  int i = 0;
  for (const auto& queueFamily : queueFamilies) {
      if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
          indices.graphicsFamily = i;
        }

      if (indices.isComplete()) {
          break;
        }

      i++;
    }

  return indices;
}
bool isDeviceSuitable(VkPhysicalDevice device) {
  QueueFamilyIndices indices = findQueueFamilies(device);

  return indices.isComplete();
}
void HelloTriangleApplication::pickPhysicalDevice()
{

  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
      throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
  for (const auto& device : devices) {

      if (isDeviceSuitable(device)) {
          physicalDevice = device;
          break;
        }
    }

  if (physicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void HelloTriangleApplication::createLogicalDevice ()
{
  //Specifying the queues to be created
  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

  VkDeviceQueueCreateInfo queueCreateInfo = {};
  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
  queueCreateInfo.queueCount = 1;

  float queuePriority = 1.0f;
  queueCreateInfo.pQueuePriorities = &queuePriority;
//Specify used device features
  VkPhysicalDeviceFeatures deviceFeatures = {};
//Create the logical device
  VkDeviceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;createInfo.pQueueCreateInfos = &queueCreateInfo;
  createInfo.queueCreateInfoCount = 1;

  createInfo.pEnabledFeatures = &deviceFeatures;
  createInfo.enabledExtensionCount = 0;

  if (enableValidationLayers) {
      createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
      createInfo.enabledLayerCount = 0;
    }
  if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
      throw std::runtime_error("failed to create logical device!");
    }
  vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}

void HelloTriangleApplication::init ()
{
  createSDLWindow ();
  createInstance ();
  pickPhysicalDevice ();
  createLogicalDevice ();
}


void HelloTriangleApplication::mainLoop ()
{
  //Main loop flag
  bool quit = false;
  //Event handler
  SDL_Event e;
  while(!quit)
    {
      //Handle events on queue
      while( SDL_PollEvent( &e ) != 0 )
        {
          //User requests quit
          if( e.type == SDL_QUIT )
            {
              quit = true;
            }
        }


    }
}

void HelloTriangleApplication::cleanup ()
{
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
