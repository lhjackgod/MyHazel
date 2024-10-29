#pragma once
#include "Hazel/Core.h"

#include "Window.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Layer.h"
#include "Hazel/LayerStack.h"
namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void Run();
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* overlayer);
	private:
		std::unique_ptr<Window> m_Window;
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	Application* createApplication();
}