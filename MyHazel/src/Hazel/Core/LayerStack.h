#pragma once
#include "Hazel/Core/Core.h"
#include "Hazel/Core/Layer.h"
namespace Hazel {
	class HAZEL_API LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();
		
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* overlayer);
		void PopLayer(Layer* layer);
		void PopOverLayer(Layer* overlayer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		int m_LayerInsert = 0;
	};
}

