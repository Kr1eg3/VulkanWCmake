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

#include <keWindow.h>
#include <keVkDevice.h>
#include <keVkRenderPass.h>
#include <keVkDescriptorSetLayout.h>
#include <keVkGraphicsPipeline.h>

typedef std::unique_ptr<KEWindow>					KEWindow_t;
typedef std::unique_ptr<KEVkDevice>					KEVkDevice_t;
typedef std::unique_ptr<KEVkRenderPass>				KEVkRenderPass_t;
typedef std::unique_ptr<KEVkGraphicsPipeline>		KEVkGraphicsPipeline_t;
typedef std::unique_ptr<KEVkDescriptorSetLayout>	KEVkDescriptorSetLayout_t;

#if NDEBUG
 const bool enableValidationLayers = false;
#else
 const bool enableValidationLayers = true;
 const std::vector<const char*> validationLayers = {
	      "VK_LAYER_KHRONOS_validation"
 };
#endif

#if 0
const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
#endif

class KEApp {
public:
	KEApp();
	~KEApp();

	// General functions
	void keRun();

private:
	// General functions
	void keInitWindow();
	void keCleanup();
	void keLoop();
	void keInitVulkan();

	// Vulkan based functions
	void drawVkFrame();
	void createVkInstance();
	void createVkSurface();
	void createVkSyncObjects();
	void createVkSwapChain();
	void createVkImageViews();
	void createVkRenderPass();
	void createVkCommandPool();
	void createVkTextureImage();
	void createVkTextureImageView();
	void createVkTextureSampler();
	void createVkFrameBuffers();
	void createVkVertexBuffer();
	void createVkIndexBuffer();
	void createVkUniformBuffers();
	void createVkDescriptorPool();
	void createVkDescriptorSets();
	void createVkDepthResources();
	void createVkCommandBuffers();
	void pickVkPhysicalDevice();
	void createVkLogicalDevice();
	void createVkGraphicsPipeline();
	void createVkDescriptiorSetLayout();

	void VkLoadModel();
#if !NDEBUG
	void setupVkDebugMessenger();
#endif
	bool checkVkValidationLayerSupport();
	std::vector<const char*> getVkRequiredExtensions();
	void populateVkDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

private:
	KEWindow_t										m_keWindow;
	KEVkDevice_t									m_keDevice;
	KEVkRenderPass_t								m_keRenderPass;
	KEVkGraphicsPipeline_t							m_keGraphicsPipeline;
	KEVkDescriptorSetLayout_t						m_keDescriptorSetLayout;

	// TODO: May be use ptr's?
	VkInstance										m_instance;
	VkSurfaceKHR									m_surface;
	VkDebugUtilsMessengerEXT						m_debugMessenger;
	VkQueue											m_presentQueue;
	VkQueue											m_graphicsQueue;

};

