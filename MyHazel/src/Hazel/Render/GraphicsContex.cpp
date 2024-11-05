#include "hzpch.h"
#include "Hazel/Render/GraphicsContex.h"

#include "Hazel/Render/Renderer.h"
#include "Platform/OpenGL/OpenGLContex.h"
namespace Hazel {
	Scope<GraphicsContex> Hazel::GraphicsContex::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLContex>(static_cast<GLFWwindow*>(window));
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
