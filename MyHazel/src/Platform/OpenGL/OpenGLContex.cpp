#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "OpenGLContex.h"
namespace Hazel {
	OpenGLContex::OpenGLContex(GLFWwindow* window)
		:m_WindowHandle(window)
	{
		HZ_CORE_ASSERT(window, "window handle is null");
	}
	void OpenGLContex::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "failed to initialize glad");
	}
	void OpenGLContex::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
