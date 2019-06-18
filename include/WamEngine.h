#ifndef WAM_ENGINE_H
#define WAM_ENGINE_H

#define VULKAN_ENABLE_LUNARG_VALIDATION

#include <SDL.h>
#include <SDL_vulkan.h>

#include <vulkan/vulkan.h>

#include <Windows.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <optional>
#include <set>
#include <algorithm>
#include <fstream>
#include <vk_utils.h>
#include <array>
#include <valarray>
#include <map>
#include <string>
#include <math.h>


#include <input..h>
#include <model.h>
#include <camera.h>
#include <pipeline.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <chrono>

struct UniformBufferObject
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec4 lightPos;
	glm::vec4 lightColor;
	glm::vec4 viewPos;
	glm::vec4 specular;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
	bool IsComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif



class WamEngine
{
public:
	void run();

private:
	void initWindow();

	void initVulkan();
	void mainLoop();
	void cleanup();

#pragma region Initialization vukan
	void CreateInstance();
	void SetupDebugMessenger();
	void CreateSurface();
	void PickPhysicalDevice();
	void CreateLogicalDevice();
	void CreateSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void CreateDescriptorSetLayout();
	void CreateGraphicsPipeline();
	void CreateFrameBuffers();
	void CreateCommandPool();
	void CreateDepthResources();
	void LoadModel();
	void CreateTextureImage();
	void CreateTextureImageView();
	void CreateTextureSampler();
	void CreateUniformBuffers();
	void CreateDescriptorPool();
	void CreateDescriptorSets();
	void CreateCommandBuffers();
	void CreateSyncObjects();
#pragma endregion 

	bool CheckValidationLayerSupport();
	std::vector<const char*> GetRequiredExtensions();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	void UpdateDescriptorSets(int modelIndex);

	void DrawFrame();

	void CreateImage(
		uint32_t width,
		uint32_t height,
		uint32_t mipLevels,
		VkSampleCountFlagBits numSamples,
		VkFormat format,
		VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkImage& image,
		VkDeviceMemory& imageMemory
	);

	static std::vector<char> ReadFile(const std::string& filename);

	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	VkCommandBuffer BeginSingleTimeCommands();
	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	void RecreateSwapChain();
	void CleanUpSwapChain();

	void GenerateMipmaps(VkImage image, VkFormat imageFormat, uint32_t texWidth, uint32_t texHeight, uint32_t mipLevels);

	void UpdateUniformBuffer(uint32_t currentImage);

	VkSampleCountFlagBits GetMaxUsableSampleCount();

	void CreateColorResources();

	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat FindDepthFormat();
	bool HasStencilComponent(VkFormat format);

	static void framebufferResizeCallback(SDL_Window* window, int width, int height);

	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	VkResult CreateDebugUtilsMessengerEXT(	VkInstance instance,
											const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
											const VkAllocationCallbacks* pAllocator,
											VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT(	VkInstance instance,
										VkDebugUtilsMessengerEXT debugMessenger,
										const VkAllocationCallbacks* pAllocator);

	static VkBool32 DebugCallBack(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSecurity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData,
		void* pUserData
	);


	// pipeline Section
	inline VkPipelineInputAssemblyStateCreateInfo PipelineInputAssemblyStateInitializer(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable);
	inline VkPipelineRasterizationStateCreateInfo PipelineRasterizationStateInitializer(VkPolygonMode polygonMode, VkCullModeFlags cullMode, VkFrontFace frontFace);
	inline VkPipelineColorBlendAttachmentState PipelineColorBlendAttachmentInitializer(VkColorComponentFlags colorWriteMask, VkBool32 blendEnable);
	inline VkPipelineColorBlendStateCreateInfo PipelineColorBlendStateInitializer(uint32_t attachmentCount, const VkPipelineColorBlendAttachmentState* pAttachement);
	inline VkPipelineDepthStencilStateCreateInfo PipelineDepthStencilStateInitializer(VkBool32 depthTestEnable, VkBool32 depthWritenable, VkCompareOp depthCompareOp);
	inline VkPipelineViewportStateCreateInfo PipelineViewportStateInitializer(uint32_t viewportCount, uint32_t scissorCount);
	inline VkPipelineMultisampleStateCreateInfo PipelineMultisampleStateInitializer(VkSampleCountFlagBits rasterizationSamples);
	inline VkPipelineDynamicStateCreateInfo PipelineDynamicStateInitializer(const std::vector<VkDynamicState>& pDynamicStateEnable);
	inline VkPipelineVertexInputStateCreateInfo PipelineVertexInputStateInitializer();

	VkPipelineShaderStageCreateInfo LoadShader(std::string shaderPath, VkShaderStageFlagBits shaderTypeFlag);


	void AddGround(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void AddStrangeCube(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void AddLightPillar(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void AddSteps(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void AddEntrance(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

	// Variables :
	SDL_Window* window;
	VkSurfaceKHR surface;
	VkInstance instance;
	SDL_Event e;
	InputManager inputManager;

	VkDevice device;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFrameBuffers;

	VkDebugUtilsMessengerEXT debugMessenger;

	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;

	std::vector<VkShaderModule> shaderModules;
	
	VkRenderPass renderPass;

	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

	const int MAX_FRAME_IN_FLIGHT = 2;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;

	std::vector<VkFence> inFlightFences;

	size_t currentFrame = 0;

	bool frameBufferResized = false;

	std::vector <std::vector<VkBuffer>> uniformBuffers;
	std::vector <std::vector<VkDeviceMemory>> uniformBufferMemory;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

	VkImage colorImage;
	VkDeviceMemory colorImageMemory;
	VkImageView colorImageView;


	PipelineManager pipelineManager;

	// CAMERA SECTION
	Camera camera;

	float dt;
	float lastFrame = 0;


	const int HEIGHT = 600;
	const int WIDTH = 800;

	const int SCREEN_CENTER_X = 767;
	const int SCREEN_CENTER_Y = 431;

	const float NEAR_DISTANCE = 0.1f;
	const float FAR_DISTANCE = 10000.0f;

	const float FOV = 60.0f;

	const float CAMERA_SPEED = 5.0f;
	const float CAMERA_SENSITIVITY = 0.5f;

	const glm::vec3 START_POSITION = glm::vec3(0, 0, 0);
	const glm::vec3 START_FRONT = glm::vec3(0, 0, 0);

	bool moveMouse = false;

	// MODELS SECTION
	std::vector<Model> models;

	std::vector<std::string> modelsPaths;
	std::vector<std::string> texturesPaths;
	std::vector<MODEL::Type> modelsType;
	std::vector<glm::vec3> modelsPosition;
	std::vector<glm::vec3> modelsScale;
	std::vector<glm::vec3> modelsRotation;
	

	std::vector<UniformBufferObject> UBOs;

	const glm::vec4 SPECULAR_WOOD{ 0.3f, 16.0f, 0, 0 };
	const glm::vec4 SPECULAR_SHINY{ 0.7f, 4.0f, 0, 0 };


	bool quit = false;
};
#endif