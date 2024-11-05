#include "SandBox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Render/Buffer.h"
SandBox2D::SandBox2D()
	:Layer("SannBox2D"),m_CameraController(1280.0f / 720.0f)
{
}

void SandBox2D::OnAttach()
{
	
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();
	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f,1.0f }, m_SquareColor);
	Hazel::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
