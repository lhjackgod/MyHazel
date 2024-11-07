#include "SandBox2D.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Hazel/Render/Buffer.h"

SandBox2D::SandBox2D()
	:Layer("SannBox2D"),m_CameraController(1280.0f / 720.0f, true)
{
}

void SandBox2D::OnAttach()
{
	m_CheckboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Hazel::Timestep ts)
{
	HZ_PROFILE_FUNCTION();
	
	HZ_PROFILE_SCOPE("CameraController");
	m_CameraController.OnUpdate(ts);
	
	
	HZ_PROFILE_SCOPE("Renderer Prep");
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();
	
	Hazel::Renderer2D::ResetStats();
	static float rotation = 0.0f;
	rotation += ts * 50.0f;
	HZ_PROFILE_SCOPE("Renderer Draw");
	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckboardTexture, 10.0f);
	Hazel::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckboardTexture, 20.0f);
	Hazel::Renderer2D::EndScene();
	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.0f; y += 0.5f) {
		for (float x = -5.0f; x < 5.0f; x += 0.5f) {
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Hazel::Renderer2D::DrawQuad({ x,y }, { 0.45f,0.45f }, color);
		}
	}
	Hazel::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender()
{
	HZ_PROFILE_FUNCTION();
	ImGui::Begin("Setting");
	auto state = Hazel::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", state.DrawCalls);
	ImGui::Text("Quads: %d", state.QuadCount);
	ImGui::Text("Vertices: %d", state.GetTotalVertexCount());
	ImGui::Text("Indices: %d", state.GetTotalIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
