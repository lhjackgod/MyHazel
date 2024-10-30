#pragma once
#include "Hazel/Render/GraphicsContex.h"
struct GLFWwindow;
namespace Hazel {
	class OpenGLContex : public GraphicsContex
	{
	public:
		OpenGLContex(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

