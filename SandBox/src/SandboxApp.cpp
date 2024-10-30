#include <Hazel.h>
#include <stdio.h>

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("example") {}
	void OnUpdate() override {
		HZ_INFO("ExampleLayer::Update");
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB)) {
			HZ_TRACE("Table key is pressed");
		}
	}
	void OnEvent(Hazel::Event& event) override{
		HZ_TRACE("{0}", event.ToString());
		if (event.GetEventType() == Hazel::EventType::KeyPressed) {
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_TAB) {
				HZ_TRACE("table key is pressed (event)!");
			}
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
	
};
class Sanbox : public Hazel::Application {
public:
	Sanbox() { 
		PushLayer(new ExampleLayer());
		//PushOverLayer(new Hazel::ImGuiLayer());
	}
	~Sanbox() { printf("delete Sanbox\n"); }

};
Hazel::Application* Hazel::createApplication() {
	return new Sanbox();
}