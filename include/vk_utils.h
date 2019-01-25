//
// Created by efarhan on 1/18/19.
//

#ifndef GPR5300_VK_UTILS_H
#define GPR5300_VK_UTILS_H

#include <vulkan/vulkan.h>
#include <vector>

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

#endif //GPR5300_VK_UTILS_H
