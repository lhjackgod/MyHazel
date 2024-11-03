#pragma once
#include "Hazel/Render/RenderCommand.h"
#include "Hazel/Render/OrthographicsCamera.h"
#include "Hazel/Render/Shader.h"
namespace Hazel {
	class Renderer {
	public:
		static void Init();
		static void BeginScene(OrthographicsCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray,
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

