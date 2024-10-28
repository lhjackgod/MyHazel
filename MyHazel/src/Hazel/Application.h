#pragma once
#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"
#include <Hazel/Events/ApplicationEvent.h>
#include "Window.h"
namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
	};
	Application* createApplication();
}