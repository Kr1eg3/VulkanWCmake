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

#include <keVkDescriptorSetLayout.h>

KEVkDescriptorSetLayout::KEVkDescriptorSetLayout() {

}

KEVkDescriptorSetLayout::~KEVkDescriptorSetLayout() {

}

void KEVkDescriptorSetLayout::createDescriptiorSetLayout(VkDevice vkDevice) {
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding samplerLayoutBinding{};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	KE_VK_CHECK(vkCreateDescriptorSetLayout(vkDevice, &layoutInfo, nullptr, &m_descriptorSetLayout));
}

VkDescriptorSetLayout KEVkDescriptorSetLayout::getDescriptorSetLayout() {
	return m_descriptorSetLayout;
}
