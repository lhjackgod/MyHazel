#include "hzpch.h"
#include "Hazel/Render/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Hazel {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}