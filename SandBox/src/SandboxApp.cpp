#include "Hazel.h"
#include "Hazel/Core/EntryPoint.h"
#include <stdio.h>

#include "SandBox2D.h"
#include "ExampleLayer.h"
class Sanbox : public Hazel::Application {
public:
	Sanbox() {
		
		PushLayer(new ExampleLayer());
		//PushLayer(new SandBox2D());
	}
	~Sanbox() { printf("delete Sanbox\n"); }

};
Hazel::Application* Hazel::createApplication() {
	return new Sanbox();
}