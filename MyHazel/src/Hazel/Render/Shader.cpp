#include "hzpch.h"
#include "Shader.h"
#include <glad/glad.h>
Hazel::Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* source = vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, NULL);
	glCompileShader(vertexShader);
	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vertexShader);
		HZ_CORE_ERROR("{0}", infoLog.data());
		HZ_CORE_ASSERT(false, "Vertex shader complilation failure");
		return;
	}
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fsource = fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &fsource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fragmentShader);
		HZ_CORE_ERROR("{0}", infoLog.data());
		HZ_CORE_ASSERT(false, "Vertex shader complilation failure");
		return;
	}
	m_RendererID = glCreateProgram();
	GLuint program = m_RendererID;
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		HZ_CORE_ERROR("{0}", infoLog.data());
		HZ_CORE_ASSERT(false, "Shader link failure!");
		return;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Hazel::Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Hazel::Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Hazel::Shader::Unbind() const
{
	glUseProgram(0);
}
