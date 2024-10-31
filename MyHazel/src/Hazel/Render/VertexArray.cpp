#include "hzpch.h"
#include "VertexArray.h"
#include "Hazel/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace Hazel {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
			break;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
