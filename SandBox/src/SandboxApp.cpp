#include <Hazel.h>
#include <stdio.h>
class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("example") {}
	void OnUpdate() override {
		HZ_INFO("ExampleLayer::Update");
	}
	void OnEvent(Hazel::Event& event) {
		HZ_TRACE("{0}", event.ToString());
	}
};
class Sanbox : public Hazel::Application {
public:
	Sanbox() { 
		PushLayer(new ExampleLayer());
		PushOverLayer(new Hazel::ImGuiLayer());
	}
	~Sanbox() { printf("delete Sanbox\n"); }

};
Hazel::Application* Hazel::createApplication() {
	return new Sanbox();
}