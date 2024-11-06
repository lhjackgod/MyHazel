#pragma once
#include "Hazel/Core/Core.h"
#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::createApplication();
int main(int arg, char** argv) {
	Hazel::Log::Inint();
	HZ_PROFILE_BEGIN_SESSION("startup", "HazelProfile-Startup.json");
	Hazel::Application* app = Hazel::createApplication();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	HZ_PROFILE_END_SESSION();

	HZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
	delete app;
	HZ_PROFILE_END_SESSION();
}
#endif