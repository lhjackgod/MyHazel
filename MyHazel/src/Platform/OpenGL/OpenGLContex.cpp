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
		HZ_CORE_INFO("OpenGL 信息:");
		HZ_CORE_INFO("	Vendor：{0}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("	显卡名：{0}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("	版本：{0}", (const char*)glGetString(GL_VERSION));

	}
	void OpenGLContex::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
