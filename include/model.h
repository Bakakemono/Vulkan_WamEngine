#ifndef MODEL_H
#define MODEL_H


#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <vulkan/vulkan.h>

#include <glm/mat4x2.hpp>
#include <vector>
#include <array>

#include "buffer.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>


struct Vertex {
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;

	static std::array<VkVertexInputBindingDescription, 1> getBindingDescriptions()
	{
		std::array<VkVertexInputBindingDescription, 1> bindingDescriptions = {};

		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescriptions;
	}
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1,
		attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, texCoord);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, normal);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other) const
	{
		return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
	}
};

template<> struct std::hash<Vertex> {
	size_t operator()(Vertex const& vertex) const {
		return ((std::hash<glm::vec3>()(vertex.pos) ^ (std::hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^ (std::hash<glm::vec2>()(vertex.texCoord) << 1);
	}
};

class Model
{
public:
	Model(const std::string path, VkPipeline* pipeline, VkDevice& device, VkPhysicalDevice& physicalDevice, VkQueue& graphicQueue, VkCommandPool& commandPool);
 
	// class members
	std::string path;
	glm::mat4 model;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	uint32_t mipLevels;

	VkImageView textureImageView;
	VkSampler textureSampler;

	VkPipeline* pipeline;

private:
	void LoadModel();
	void CreateVertexBuffer(
		VkDevice& device,
		VkPhysicalDevice& physicalDevice,
		VkQueue& graphicsQueue, 
		VkCommandPool& commandPool
	);

	void CreateIndexBuffer(
		VkDevice& device,
		VkPhysicalDevice& physicalDevice,
		VkQueue& graphicsQueue,
		VkCommandPool& commandPool
	);
};

#endif
