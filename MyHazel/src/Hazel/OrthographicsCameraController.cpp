#include "hzpch.h"
#include "OrthographicsCameraController.h"
#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"
namespace Hazel {
	OrthographicsCameraController::OrthographicsCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio),m_Camera(-m_AspectRatio * m_ZoomLevel,m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),m_Rotation(rotation)
	{
	}
	void OrthographicsCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(HZ_KEY_A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(HZ_KEY_W)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_S)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}
		if (m_Rotation) {
			if (Input::IsKeyPressed(HZ_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			else if (Input::IsKeyPressed(HZ_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}
			m_Camera.SetRotation(m_CameraRotation);
		}
		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}
	void OrthographicsCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicsCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicsCameraController::OnWindowResize));
	}
	bool OrthographicsCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;

	}
	bool OrthographicsCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}