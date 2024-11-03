#pragma once
#include "Hazel/Render/Shader.h"
#include <glm/glm.hpp>
namespace Hazel {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& verFile, const std::string& fragFile);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		
		std::string ReadFile(const std::string filepath);
		std::unordered_map<unsigned int, std::string> PreProcess(const std::string& verSrc, const std::string& fragSrc);
		void Compile(const std::unordered_map<unsigned int, std::string>& shaderSources);
	private:
		uint32_t m_RendererID;
	};
}

