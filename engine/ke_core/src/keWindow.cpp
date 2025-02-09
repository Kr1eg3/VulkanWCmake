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


#include <keWindow.h>

KEWindow::KEWindow()
	: m_height  {800}
	, m_width   {800}
	, m_winName {"Default Vulkan Name"} {

}

KEWindow::~KEWindow() {

}

GLFWwindow* KEWindow::getPtrWin() {
	return m_window;
}

void KEWindow::initWin() {
	if (!glfwInit()) {
		printf("GLWF Failed init");
		return;
	}

	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(m_width, m_height, m_winName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_window, this);
	//glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
}
