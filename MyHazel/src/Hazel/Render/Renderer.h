#pragma once
#include "Hazel/Render/RenderCommand.h"
#include "Hazel/Render/OrthographicsCamera.h"
#include "Hazel/Render/Shader.h"
#include "Hazel/Render/Renderer2D.h"
namespace Hazel {
	class Renderer {
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicsCamera& camera);
		static void EndScene();
		static void ShutDown();
		static void Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray,
			const glm::mat4& transform = glm::mat4(1.0));
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}

