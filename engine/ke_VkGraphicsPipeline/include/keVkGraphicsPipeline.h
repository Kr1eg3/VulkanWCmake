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

static std::vector<char> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}


class KEVkGraphicsPipeline
{
public:
	KEVkGraphicsPipeline();
	~KEVkGraphicsPipeline();

	void createGraphicsPipeline(VkDevice vkDevice, VkDescriptorSetLayout vkDescriptorSetLayout,
		VkRenderPass vkRenderPass);

	KE_INLINE VkPipeline getGraphicsPipeline() { return m_graphicsPipeline; }
	KE_INLINE VkPipelineLayout getPipelineLayout() { return m_pipelineLayout; }

private:
	VkShaderModule createShaderModule(VkDevice vkDevice, const std::vector<char>& code);


private:
	VkPipeline										m_graphicsPipeline;
	VkPipelineLayout								m_pipelineLayout = VK_NULL_HANDLE;
};

