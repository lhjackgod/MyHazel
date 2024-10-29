#pragma once
#include "Hazel/Layer.h"
namespace Hazel {
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnUpdate();
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
	private:
		float m_Time = 0.0f;
	};
}

