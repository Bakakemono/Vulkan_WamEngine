#ifndef BUFFER_H
#define BUFFER_H

#include <vulkan/vulkan.h>
#include <stdexcept>

class Buffer
{
public :
	static void CreateBuffer(
		VkDevice& device, 
		VkPhysicalDevice& physicalDevice, 
		VkDeviceSize size, VkBufferUsageFlags usage, 
		VkMemoryPropertyFlags properties,
		VkBuffer& buffer,
		VkDeviceMemory& bufferMemory);

	static uint32_t FindMemoryType(
		VkPhysicalDevice& physicalDevice,
		uint32_t typeFilter,
		VkMemoryPropertyFlags properties
	);

	static void CopyBuffer(
		VkBuffer srcBuffer,
		VkBuffer dstBuffer,
		VkDeviceSize size,
		VkDevice& device,
		VkQueue& graphicsQueue,
		VkCommandPool& commandPool
	);

	static VkCommandBuffer BeginSingleTimeCommands(VkDevice& device, VkCommandPool& commandPool);
	static void EndSingleTimeCommands(VkDevice& device, VkCommandBuffer commandBuffer, VkQueue& graphicsQueue, VkCommandPool& commandPool);
};

#endif