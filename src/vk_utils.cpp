//
// Created by efarhan on 1/18/19.
//
#include <vector>
#include <vk_utils.h>
#include <vulkan/vulkan.h>

bool checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  return false;
}
