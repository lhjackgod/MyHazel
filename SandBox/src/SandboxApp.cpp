#include <Hazel.h>
#include <stdio.h>
class Sanbox : public Hazel::Application {
public:
	Sanbox() { printf("create Sanbox\n"); }
	~Sanbox() { printf("delete Sanbox\n"); }

};
Hazel::Application* Hazel::createApplication() {
	return new Sanbox();
}