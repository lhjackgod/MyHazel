#include "hzpch.h"
#include "Hazel/Render/Shader.h"
#include "Hazel/Render/Renderer2D.h"
#include "Hazel/Render/VertexArray.h"
#include "Hazel/Render/RenderCommand.h"
#include <glm/gtc/type_ptr.hpp>
namespace Hazel {
	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};
	static Renderer2DStorage* s_Data;
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices,sizeof(squareVertices)));
		squareVB->SetLayout({
			{Hazel::ShaderDataType::Float3,"a_Position"},
			{Hazel::ShaderDataType::Float2,"a_TexCoord"}
			});
		Ref<IndexBuffer> squareIB;
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
		s_Data->WhiteTexture = Texture2D::Create(1,1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.Ver", "assets/shaders/Texture.Frag");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}
	void Renderer2D::BeginScene(const OrthographicsCamera& camera)
	{

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->TextureShader->Bind();
		glm::mat4 t = glm::translate(glm::mat4(1.0), position);
		s_Data->TextureShader->SetMat4(
			"u_Transform",
			glm::scale(
				glm::translate(glm::mat4(1.0f),position),
				glm::vec3(size.x,size.y,1.0f)
			)
		);
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();
		s_Data->QuadVertexArray->Bind();
		Hazel::RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), size, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Data->TextureShader->Bind();
		texture->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data->TextureShader->SetMat4(
			"u_Transform",
			glm::scale(
				glm::translate(glm::mat4(1.0f), position),
				glm::vec3(size.x, size.y, 1.0f)
			)
		);
		s_Data->QuadVertexArray->Bind();
		
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}