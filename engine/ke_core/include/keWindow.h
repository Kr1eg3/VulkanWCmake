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

#if 0
struct DestroyglfwWin{

	void operator()(GLFWwindow* ptr) {
		glfwDestroyWindow(ptr);
	}

};
#endif

class KEWindow {

public:
	KEWindow();
	~KEWindow();

	void initWin();
	GLFWwindow* getPtrWin();

private:
	uint16_t m_height;
	uint16_t m_width;
	std::string m_winName;

	GLFWwindow* m_window;


};



