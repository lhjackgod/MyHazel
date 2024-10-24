#include "Hazel/Application.h"
#include "Hazel/Log.h"
#include "Hazel/Events/ApplicationEvent.h"
#include <iostream>
namespace Hazel {
	Application::Application(){}
	Application::~Application(){}
	void Application::Run() {
		WindowResizeEvent e(100, 100);
		if (e.IsInCategory(EventCategoryApplication)) {
			HZ_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput)) {
			HZ_TRACE(e.ToString());
		}
		
		while (true)
		{
			
		}
	}
}
