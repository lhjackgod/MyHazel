#include "hzpch.h"
#include "Shader.h"
#include "Hazel/Render/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Hazel {
	Shader* Shader::Create(const std::string& verFile, const std::string& fragFile)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(verFile,fragFile);
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}