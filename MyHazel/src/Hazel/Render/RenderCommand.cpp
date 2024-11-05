#include "hzpch.h"
#include "Hazel/Render/RenderCommand.h"
namespace Hazel{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}