#include "hzpch.h"
#include "WindowsWindow.h"
namespace Hazel {
	static bool is_GLFWInitialized = false;
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}
	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Create Window {0} ({1} {2})", m_Data.Title, m_Data.Width, m_Data.Height);
		if (!is_GLFWInitialized) {
			int sucess = glfwInit();
			HZ_CORE_ASSERT(sucess, "Could not intialize GLFW!");
			is_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}