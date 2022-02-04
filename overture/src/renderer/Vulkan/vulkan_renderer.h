#pragma once

#include <renderer/renderer.h>

#include <cstdint>
#include <defines.h>

#include <string>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include <vector>
#include <optional>

#include <GLFW/glfw3.h>

#include <array>

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::string MODEL_PATH = "../overture/res/viking_room.obj";
const std::string TEXTURE_PATH = "../overture/res/viking_room.png";

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	b8 isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

//TODO: remove after fixing math.h
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    	return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }

	bool operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }
};

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class VulkanRenderer final : public Renderer {
	public:
		virtual void init() override;
		virtual void shutdown() override;

		virtual void drawFrame() override;
		
		static void onResize(GLFWwindow* window, i32 width, i32 height);

	private:
		b8 createInstance();
		void setupDebugCallback();
		void createSurface();
		VkPhysicalDevice pickPhysicalDevice();
		void createLogicalDevice();
		void createSwapChain();
		void createImageViews();
		void createGraphicsPipeline();
		void createRenderPass();
		void createFrameBuffers();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();
		void recreateSwapChain();
		void cleanupSwapChain();
		void createDescriptorSetLayout();
		void createUniformBuffers();
		void updateUniformBuffer(uint32_t currentImage);
		void createDescriptorPool();
		void createDescriptorPoolSets();

		void createVertexBuffer();
		void createIndexBuffer();
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		VkCommandBuffer beginSingleTimeCommands();
		void endSingleTimeCommands(VkCommandBuffer commandBuffer);

		void createTextureImage();
		void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void createTextureImageView();
		VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
		void createTextureSampler();

		void createDepthResources();
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat();
		b8 hasStencilComponent(VkFormat format);

		void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

		b8 checkValidationLayerSupport();
		b8 validationLayerSupported;
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

		b8 isDeviceSuitable(VkPhysicalDevice device);
		b8 checkDeviceExtensionSupport(VkPhysicalDevice device);

		std::vector<const char*> getRequiredExtensions();

		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		VkShaderModule createShaderModule(const std::vector<char>& code);

		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

		void loadModel();

		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice logicalDevice;
		VkQueue graphicsQueue;
		VkSurfaceKHR surface;
		VkQueue presentQueue;
		VkSwapchainKHR swapChain;
		VkRenderPass renderPass;
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		VkCommandPool commandPool;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;
		VkDescriptorPool descriptorPool;
		std::vector<VkDescriptorSet> descriptorSets;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;
		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
		size_t currentFrame = 0;

		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFramebuffers;
		std::vector<VkCommandBuffer> commandBuffers;

		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		const std::vector<const char*> validationLayers = {
    		"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> deviceExtensions = {
		    VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
};
