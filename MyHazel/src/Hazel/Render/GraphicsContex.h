#pragma once
namespace Hazel {
	class GraphicsContex
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		static Scope<GraphicsContex> Create(void* window);
	};
}