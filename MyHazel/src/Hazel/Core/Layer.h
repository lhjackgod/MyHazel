#pragma once
#include "Hazel/Core/Base.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/Timestep.h"
namespace Hazel {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender(){}
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

