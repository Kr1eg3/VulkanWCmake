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

#include <keApp.h>


KEApp::KEApp() {
	m_keWindow = std::make_unique<KEWindow>();
#if !NDEBUG
	m_keDevice = std::make_unique<KEVkDevice>(validationLayers);
#else
	m_keDevice = std::make_unique<KEVkDevice>(validationLayers);
#endif
	m_keRenderPass = std::make_unique<KEVkRenderPass>();
	m_keGraphicsPipeline = std::make_unique<KEVkGraphicsPipeline>();
	m_keDescriptorSetLayout = std::make_unique<KEVkDescriptorSetLayout>();

}

KEApp::~KEApp() {

}

void KEApp::keRun() {
	keInitWindow();
	keInitVulkan();
	keLoop();
	keCleanup();
}

void KEApp::keInitWindow() {
	m_keWindow->initWin();
}

void KEApp::keInitVulkan() {
	createVkInstance();
#if !NDEBUG
	setupVkDebugMessenger();
#endif
	createVkSurface();
	pickVkPhysicalDevice();
	createVkLogicalDevice();
	createVkSwapChain();
	createVkImageViews();
	createVkRenderPass();
	createVkDescriptiorSetLayout();
	createVkGraphicsPipeline();
	createVkCommandPool();
	createVkDepthResources();
	createVkFrameBuffers();
	createVkTextureImage();
	createVkTextureImageView();
	createVkTextureSampler();
	VkLoadModel();
	createVkVertexBuffer();
	createVkIndexBuffer();
	createVkUniformBuffers();
	createVkDescriptorPool();
	createVkDescriptorSets();
	createVkCommandBuffers();
	createVkSyncObjects();
}

void KEApp::drawVkFrame() {
	auto win = m_keWindow->getPtrWin();
	auto keRenderPass = m_keRenderPass->getRenderPass();
	auto keGraphicsPipeline = m_keGraphicsPipeline->getGraphicsPipeline();
	auto kePipelineLayout = m_keGraphicsPipeline->getPipelineLayout();

	m_keDevice->drawFrame(win, m_surface, keRenderPass, keGraphicsPipeline,
		kePipelineLayout, m_presentQueue, m_graphicsQueue);
}

void KEApp::createVkInstance() {
	if (enableValidationLayers && !checkVkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Kovalskiy App";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Kovalskiy Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3; // Concrete Vulkan API version for now

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = getVkRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT createDebugInfo{};
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateVkDebugMessengerCreateInfo(createDebugInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&createDebugInfo;
	} else {
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}

	KE_VK_CHECK(vkCreateInstance(&createInfo, nullptr, &m_instance));
}

void KEApp::createVkSurface() {
	auto keWin = m_keWindow->getPtrWin();
	assert(keWin != nullptr);
	KE_VK_CHECK(glfwCreateWindowSurface(m_instance, keWin, nullptr, &m_surface));
}

void KEApp::createVkSyncObjects() {
	m_keDevice->createSyncObjects();
}

void KEApp::createVkSwapChain() {
	auto keWin = m_keWindow->getPtrWin();
	assert(keWin != nullptr);
	m_keDevice->createSwapChain(keWin, m_surface);
}

void KEApp::createVkImageViews() {
	m_keDevice->createImageViews();
}

void KEApp::createVkRenderPass() {
	auto keDevice      = m_keDevice->getDevice();
	auto kePhysDevice  = m_keDevice->getPhysDevice();
	auto keSCImgFormat = m_keDevice->getSwapChainImgFormat();
	m_keRenderPass->createRenderPass(keDevice, kePhysDevice, keSCImgFormat);
}

void KEApp::createVkCommandPool() {
	m_keDevice->createCommandPool(m_surface);
}

void KEApp::createVkTextureImage() {
	m_keDevice->createTextureImage(m_graphicsQueue);
}

void KEApp::createVkTextureImageView() {
	m_keDevice->createTextureImageView();
}

void KEApp::createVkTextureSampler() {
	m_keDevice->createTextureSampler();
}

void KEApp::createVkFrameBuffers() {
	auto keRenderPass  = m_keRenderPass->getRenderPass();
	m_keDevice->createFramebuffers(keRenderPass);
}

void KEApp::createVkVertexBuffer() {
	m_keDevice->createVertexBuffer(m_graphicsQueue);
}

void KEApp::createVkIndexBuffer() {
	m_keDevice->createIndexBuffer(m_graphicsQueue);
}

void KEApp::createVkUniformBuffers() {
	m_keDevice->createUniformBuffers();
}

void KEApp::createVkDescriptorPool() {
	m_keDevice->createDescriptorPool();
}

void KEApp::createVkDescriptorSets() {
	auto keDescrSetLayout = m_keDescriptorSetLayout->getDescriptorSetLayout();
	m_keDevice->createDescriptorSets(keDescrSetLayout);
}

void KEApp::createVkDepthResources() {
	m_keDevice->createDepthResources();
}

void KEApp::createVkCommandBuffers() {
	m_keDevice->createCommandBuffers();
}

void KEApp::pickVkPhysicalDevice() {
	m_keDevice->pickVkPhysicalDevice(m_instance, m_surface);
}

void KEApp::createVkLogicalDevice() {
	m_keDevice->createLogicalDevice(m_presentQueue, m_graphicsQueue, m_surface);
}

void KEApp::createVkGraphicsPipeline() {
	auto keDevice      = m_keDevice->getDevice();
	auto keRenderPass  = m_keRenderPass->getRenderPass();
	auto keDSL		   = m_keDescriptorSetLayout->getDescriptorSetLayout();

	m_keGraphicsPipeline->createGraphicsPipeline(keDevice, keDSL, keRenderPass);
}

void KEApp::createVkDescriptiorSetLayout() {
	auto keDevice      = m_keDevice->getDevice();
	m_keDescriptorSetLayout->createDescriptiorSetLayout(keDevice);
}

void KEApp::VkLoadModel() {
	m_keDevice->loadModel();
}

void KEApp::keCleanup() {


	glfwTerminate();
}

void KEApp::keLoop() {
	auto keWin = m_keWindow->getPtrWin();
	assert(keWin != nullptr);

	while (!glfwWindowShouldClose(keWin)) {
		glfwPollEvents();
		drawVkFrame();
	}
}


bool KEApp::checkVkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;

			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

std::vector<const char*> KEApp::getVkRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		 extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void KEApp::populateVkDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
								| VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
								| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
								| VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
								| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}

#if !NDEBUG
void KEApp::setupVkDebugMessenger() {
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createDebugInfo;
	populateVkDebugMessengerCreateInfo(createDebugInfo);
	KE_VK_CHECK(CreateDebugUtilsMessengerEXT(m_instance, &createDebugInfo, nullptr,
		&m_debugMessenger));
}
#endif

