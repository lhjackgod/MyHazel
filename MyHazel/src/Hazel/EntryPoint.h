#pragma once
#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::createApplication();
int main(int arg, char** argv) {
	Hazel::Log::Inint();
	Hazel::Log::GetCoreLogger()->warn("jackgod");
	Hazel::Log::GetClientLogger()->error("hahha");

	HZ_CORE_ERROR("llll{0}{1}", 123, 2);
	Hazel::Application* app = Hazel::createApplication();
	app->Run();
	delete app;
}
#endif