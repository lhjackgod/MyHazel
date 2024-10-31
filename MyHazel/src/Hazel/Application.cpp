#include "hzpch.h"
#include "Hazel/Application.h"
#include "Hazel/Log.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Platform/Windows/WindowsWindow.h"
namespace Hazel {
	
	Application* Application::s_Instance = nullptr;
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
	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(HZ_BIND_EVENT_FN(Hazel::Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		unsigned int indices[3] = { 0, 1, 2 };
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			BufferLayout layout = {
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};
			m_VertexBuffer->SetLayout(layout);
		}
		m_VertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized? GL_TRUE:GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
				);
			index++;
		}
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position,1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 FragColor;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				FragColor = v_Color;
			}
		)";
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}
	Application::~Application(){}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(Hazel::Application::OnWindowClose));
		for (auto it = m_LayerStack.end()-1; it != m_LayerStack.begin(); it--) {
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run() {
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
			for (auto layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->onImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverLayer(Layer* overlayer)
	{
		m_LayerStack.PushOverLayer(overlayer);
		overlayer->OnAttach();
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
