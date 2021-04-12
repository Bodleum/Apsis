#pragma once
#include <deque>

namespace A {

	class Layer
	{
	public:
		Layer();
		virtual ~Layer() = default;

		virtual void OnAdd();
		virtual void OnRemove();

		virtual void OnUpdate() {}

		const bool IsEnabled() const { return m_Enabled; }

	private:
		bool m_Enabled;		// for turning on and off without removing layer from stack
	};

	/*
	* Wraper for a stack of layers
	* 
	* Render loop starts at bottom and works up
	* Events start at top and are propogated down
	*/
	class LayerStack
	{
	public:
		LayerStack() = default;
		virtual ~LayerStack() = default;

		// Push and pop layers from the stack
		inline void Push(const Layer& layer)		{ m_LayerStack.push_front(layer); }
		inline void Emplace(const Layer& layer)		{ m_LayerStack.emplace_front(layer); }
		inline void Pop()							{ m_LayerStack.pop_front(); }

		inline size_t Size() const { return m_LayerStack.size(); }
		inline Layer operator[](int index) { return m_LayerStack[index]; }

	private:
		std::deque<Layer> m_LayerStack;
	};

}