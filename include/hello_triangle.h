//
// Created by efarhan on 1/18/19.
//

#ifndef GPR5300_HELLO_TRIANGLE_H
#define GPR5300_HELLO_TRIANGLE_H

#include <vector>
#include <optional>
#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

class HelloTriangleApplication {
 public:

  void init();

  void mainLoop();

  void cleanup();
 private:

  void createSDLWindow();
  void createInstance();
  void pickPhysicalDevice();
  void createLogicalDevice();


  SDL_Window* window;
  VkInstance instance;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkQueue graphicsQueue;
  VkDevice device;
  const std::vector<const char*> validationLayers = {
      "VK_LAYER_LUNARG_standard_validation"
  };

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
      return graphicsFamily.has_value();
    }
};

#endif //GPR5300_HELLO_TRIANGLE_H
