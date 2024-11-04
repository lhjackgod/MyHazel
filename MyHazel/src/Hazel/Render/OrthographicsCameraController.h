#pragma once
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Render/OrthographicsCamera.h"
namespace Hazel {
	class OrthographicsCameraController
	{
	public:
		OrthographicsCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		OrthographicsCamera& GetCamera() { return m_Camera; }
		const OrthographicsCamera& GetCamera() const { return m_Camera; }
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicsCamera m_Camera;
		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}

