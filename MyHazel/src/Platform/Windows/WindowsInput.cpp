#include "hzpch.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>
namespace Hazel {
	bool Input::IsKeyPressed(KeyCode key) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, key);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::pair<float, float>(static_cast<float>(xPos),static_cast<float>(yPos));
	}

	float Input::GetMouseX()
	{
		auto [x, y] = Input::GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = Input::GetMousePosition();
		return y;
	}

}