#include "hzpch.h"
#include "Hazel/Render/Buffer.h"
#include "Hazel/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Hazel/Render/RendererAPI.h"
namespace Hazel{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
				break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
			break;
		}
		HZ_CORE_ASSERT(false, "Unkonwn RendererAPI!");
		return nullptr;
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, size);
			break;
		}
		HZ_CORE_ASSERT(false, "Unkonwn RendererAPI!");
		return nullptr;
	}
}