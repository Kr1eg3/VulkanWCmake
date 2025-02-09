//           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//                     Version 3, May 2010
//
//  Everyone is permitted to copy and distribute verbatim or modified
//  copies of this license document, and changing it is allowed as long
//  as the name is changed.
//
//  This license applies to any copyrightable work with which it is
//  packaged and/or distributed, except works that are already covered by
//  another license. Any other license that applies to the same work
//  shall take precedence over this one.
//
//  To the extent permitted by applicable law, the works covered by this
//  license are provided "as is" and do not come with any warranty except
//  where otherwise explicitly stated.
//
//
//             DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
//   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION, AND MODIFICATION

#pragma once

#include <keDefines.h>
#include <keUtils.h>


const std::string TEXTURE_PATH	= "../../../resources/viking_room.png"; // TEMPORARY
const std::string MODEL_PATH	= "../../../resources/viking_room.obj";


struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() const {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR		capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR>	presentModes;
};

class KEVkDevice {
public:
	KEVkDevice();
#if !NDEBUG
	KEVkDevice(std::vector<const char*> validationLayers);
#endif
	~KEVkDevice();
	void drawFrame(GLFWwindow* window, VkSurfaceKHR vkSurface,
	VkRenderPass vkRenderPass, VkPipeline vkGraphicsPipeline,
	VkPipelineLayout vkPipelineLayout, VkQueue& vkPresentQueue, VkQueue& vkGraphicsQueue);
	void pickVkPhysicalDevice(VkInstance vkInstance, VkSurfaceKHR vkSurface);
	void createLogicalDevice(VkQueue& vkPresentQueue, VkQueue& vkGraphicsQueue, VkSurfaceKHR vkSurface);
	void createSwapChain(GLFWwindow* window, VkSurfaceKHR vkSurface);
	void createCommandPool(VkSurfaceKHR vkSurface);
	void createDepthResources();
	void createImageViews();
	void createTextureImageView();
	void createTextureSampler();
	void createIndexBuffer(VkQueue vkGraphicsQueue);
	void createUniformBuffers();
	void createDescriptorPool();
	void createDescriptorSets(VkDescriptorSetLayout vkDescriptorSetLayout);
	void createCommandBuffers();
	void createSyncObjects();
	void createTextureImage(VkQueue vkGraphicsQueue);
	void createFramebuffers(VkRenderPass vkRenderPass);
	VkDevice getDevice();
	VkPhysicalDevice getPhysDevice();
	KE_INLINE VkSwapchainKHR getSwapChain() { return m_swapChain; }
	KE_INLINE std::vector<VkFence> getInFlightFences() { return m_inFlightFences; }
	KE_INLINE std::vector<VkSemaphore> getImageAvailibleSemaphores() { return m_imageAvailableSemaphores; }
	VkFormat getSwapChainImgFormat();

	void loadModel();
	void createVertexBuffer(VkQueue vkGraphicsQueue);


private:
	void createImage(uint32_t width, uint32_t height,
		VkFormat format, VkImageTiling tiling,
		VkImageUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkImage& image, VkDeviceMemory& imageMemory);
	void recreateSwapChain(GLFWwindow* window, VkSurfaceKHR vkSurface,
	VkRenderPass vkRenderPass);
	void cleanupSwapChain();
	void updateUniformBuffer(uint32_t currentImage);
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex,
		VkRenderPass vkRenderPass, VkPipeline vkGraphicsPipeline,
		VkPipelineLayout vkPipelineLayout);
	bool isVkDeviceSuitable(VkPhysicalDevice vkDevice, VkSurfaceKHR vkSurface);
	void transitionImageLayout(VkQueue vkGraphicsQueue, VkImage image, VkFormat format,
		VkImageLayout oldLayout, VkImageLayout newLayout);
	VkCommandBuffer beginSingleTimeCommands();
	void copyBuffer(VkQueue vkGraphicsQueue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkQueue vkGraphicsQueue);
	void copyBufferToImage(VkQueue vkGraphicsQueue, VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	VkFormat findDepthFormat();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
		VkImageTiling tiling, VkFormatFeatureFlags features);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	QueueFamilyIndices findVkQueueFamilies(VkPhysicalDevice vkDevice, VkSurfaceKHR vkSurface);
	bool checkDeviceExtensionSupport(VkPhysicalDevice vkDevice);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice vkDevice, VkSurfaceKHR vkSurface);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
	VkImageView createImageView(VkImage vkImage, VkFormat vkFormat, VkImageAspectFlags vkAspectFlags);



private:
	VkPhysicalDevice								m_VkPhysicalDevice	= VK_NULL_HANDLE;
	VkDevice										m_VkDevice			= VK_NULL_HANDLE;

#if !NDEBUG
	std::vector<const char*>						m_validationLayers;
#endif
	VkSwapchainKHR									m_swapChain;
	VkFormat										m_swapChainImageFormat;
	VkExtent2D										m_swapChainExtent;
	std::vector<VkImage>							m_swapChainImages;
	std::vector<VkImageView>						m_swapChainImageViews;
	std::vector<VkFramebuffer>						m_swapChainFramebuffers;
	VkCommandPool									m_commandPool;
    VkImage											m_depthImage;
    VkDeviceMemory									m_depthImageMemory;
    VkImageView										m_depthImageView;

    VkImage											m_textureImage;
    VkDeviceMemory									m_textureImageMemory;
	VkImageView										m_textureImageView;
	VkSampler										m_textureSampler;


	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	VkBuffer										m_vertexBuffer;
	VkDeviceMemory									m_vertexBufferMemory;
	VkBuffer										m_indexBuffer;
	VkDeviceMemory									m_indexBufferMemory;


	std::vector<VkBuffer>							m_uniformBuffers;
	std::vector<VkCommandBuffer>					m_commandBuffers;
	std::vector<VkDeviceMemory>						m_uniformBuffersMemory;
	std::vector <void*>								m_uniformBuffersMapped;


	VkDescriptorSetLayout							m_descriptorSetLayout;
	VkDescriptorPool								m_descriptorPool;
	std::vector<VkDescriptorSet>					m_descriptorSets;


	std::vector<VkSemaphore>						m_imageAvailableSemaphores;
	std::vector<VkSemaphore>						m_renderFinishedSemaphores;
	std::vector<VkFence>							m_inFlightFences;

	uint32_t										m_currentFrame = 0;
	bool											m_framebufferResized = false;

};

