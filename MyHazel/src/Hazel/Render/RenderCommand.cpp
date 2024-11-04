#include "hzpch.h"
#include "Hazel/Render/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
namespace Hazel{
	RendererAPI* RenderCommand::s_RendererAPI = new  OpenGLRendererAPI();
}