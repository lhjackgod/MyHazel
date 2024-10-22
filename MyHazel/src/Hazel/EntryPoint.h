#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::createApplication();
int main(int arg, char** argv) {
	Hazel::Application* app = Hazel::createApplication();
	app->Run();
	delete app;
}
#endif