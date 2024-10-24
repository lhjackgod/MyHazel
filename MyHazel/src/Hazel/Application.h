#pragma once
#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"
namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		
	};
	Application* createApplication();
}