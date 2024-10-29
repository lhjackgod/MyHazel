#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsert, layer);
		m_LayerInsert++;
	}

	void LayerStack::PushOverLayer(Layer* overlayer)
	{
		m_Layers.emplace_back(overlayer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsert, layer);
		if (it != m_Layers.begin() + m_LayerInsert) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverLayer(Layer* overlayer)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsert, m_Layers.end(), overlayer);
		if (it != m_Layers.end()) {
			overlayer->OnDetach();
			m_Layers.erase(it);
		}
	}
}
