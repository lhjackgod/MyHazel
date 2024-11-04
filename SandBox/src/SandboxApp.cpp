#include <Hazel.h>
#include <stdio.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer()
		: Layer("example"), m_CameraController(1280.0f / 720.0f)
	{
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		uint32_t indices[3] = { 0, 1, 2 };
		m_VertexArray.reset(Hazel::VertexArray::Create());

		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hazel::BufferLayout layout = {
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Hazel::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Hazel::Ref<Hazel::VertexBuffer> squareVB;
		squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{Hazel::ShaderDataType::Float3, "a_Position"},
			{Hazel::ShaderDataType::Float2,"a_TexCoord"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);
		Hazel::Ref<Hazel::IndexBuffer> squareIB;
		squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);
		
		m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");
		triangleName =
			m_ShaderLibray.Load("assets/shaders/Triangle.Ver", "assets/shaders/Triangle.Frag")->GetName();
		FlatName =
			m_ShaderLibray.Load("assets/shaders/Flat.Ver", "assets/shaders/Flat.Frag")->GetName();
		TextureName =
			m_ShaderLibray.Load("assets/shaders/Texture.Ver", "assets/shaders/Texture.Frag")->GetName();
	}
	void OnUpdate(Hazel::Timestep ts) override {
		m_CameraController.OnUpdate(ts);
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();
		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_ShaderLibray.Get(FlatName))->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_ShaderLibray.Get(FlatName))->UploadUniformFloat3("u_Color", m_SquareColor);
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazel::Renderer::Submit(m_ShaderLibray.Get(FlatName), m_SquareVA, transform);
			}
		}		
		m_Texture->Bind();
		Hazel::Renderer::Submit(m_ShaderLibray.Get(TextureName), m_SquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Hazel::Renderer::Submit(m_ShaderLibray.Get(TextureName), m_SquareVA, glm::scale(glm::mat4(1.0), glm::vec3(1.5f)));
		Hazel::Renderer::Submit(m_ShaderLibray.Get(triangleName), m_VertexArray);
		
		Hazel::Renderer::EndScene();
	}
	void OnEvent(Hazel::Event& event) override{
		
		m_CameraController.OnEvent(event);
	}
	virtual void onImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
private:
	std::string triangleName, FlatName, TextureName;
	Hazel::ShaderLibray m_ShaderLibray;
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Texture> m_Texture;
	Hazel::Ref<Hazel::Texture>  m_ChernoLogoTexture;
	Hazel::OrthographicsCameraController m_CameraController;

	glm::vec3 m_CameraPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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