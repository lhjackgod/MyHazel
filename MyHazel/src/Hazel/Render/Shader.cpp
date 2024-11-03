#include "hzpch.h"
#include "Shader.h"
#include "Hazel/Render/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Hazel {
	Ref<Shader> Shader::Create(const std::string& verFile, const std::string& fragFile)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(verFile,fragFile);
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	void ShaderLibray::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HZ_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	void ShaderLibray::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	Ref<Shader> ShaderLibray::Load(const std::string& verFile, const std::string& fragFile)
	{
		auto shader = Shader::Create(verFile, fragFile);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibray::Load(const std::string& name, const std::string& verFile, const std::string& fragFile)
	{
		auto shader = Shader::Create(verFile, fragFile);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibray::Get(const std::string& name)
	{
		HZ_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	bool ShaderLibray::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}