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

#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define MAX_FRAMES_IN_FLIGHT 2
#define ATTACHMENT_DESCRIPTION_NUM 2

#define KE_INLINE inline

#include <iostream>
#include <fstream>
#include <assert.h>
#include <chrono>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <optional>
#include <limits>
#include <map>
#include <set>
#include <array>
#include <unordered_map>


#define KE_VK_CHECK(func) {									\
	const VkResult result = func;							\
	if (result != VK_SUCCESS) {								\
		std::cerr << "Error calling function " << #func		\
				<< " at " << __FILE__ << ":"				\
				<< __LINE__ << ". Result is "				\
				<< string_VkResult(result)					\
				<< std::endl;								\
		assert(false);										\
	}														\
}



