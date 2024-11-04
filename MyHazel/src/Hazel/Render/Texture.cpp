#include "hzpch.h"
#include "Hazel/Render/Texture.h"
#include "Hazel/Render/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Hazel {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}