#include "hzpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Platform/OpenGL/OpenGLContex.h"
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
		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("	Vendor   :{0}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("	Renderer :{0}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("	Version  :{0}", (const char*)glGetString(GL_VERSION));
		HZ_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}
	void OpenGLContex::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
