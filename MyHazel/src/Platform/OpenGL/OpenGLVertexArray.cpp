#include "hzpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include <glad/glad.h>
namespace Hazel {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Float:
			return GL_FLOAT;
			break;
		case ShaderDataType::Float2:
			return GL_FLOAT;
			break;
		case ShaderDataType::Float3:
			return GL_FLOAT;
			break;
		case ShaderDataType::Float4:
			return GL_FLOAT;
			break;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
			break;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
			break;
		case ShaderDataType::Int:
			return GL_INT;
			break;
		case ShaderDataType::Int2:
			return GL_INT;
			break;
		case ShaderDataType::Int3:
			return GL_INT;
			break;
		case ShaderDataType::Int4:
			return GL_INT;
			break;
		case ShaderDataType::Bool:
			return GL_BOOL;
			break;
		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElemets().size(), "Vertex Buffer has not layout");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
				);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}