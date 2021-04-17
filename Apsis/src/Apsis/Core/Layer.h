#pragma once
#include <deque>
#include "Apsis/Event/EventDispatcher.h"

namespace A {

	class Layer : public EventListener
	{
	public:
		Layer();
		virtual ~Layer() = default;

		virtual void OnAdd() = 0;
		virtual void OnRemove() = 0;

		virtual void OnUpdate() = 0;

		const bool IsEnabled() const { return m_Enabled; }

	protected:
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
		inline void Push(Layer* layer)		{ m_LayerStack.push_front(layer); }
		inline void Emplace(Layer* layer)	{ m_LayerStack.emplace_front(layer); }
		inline void Pop()					{ m_LayerStack.pop_front(); }

		inline Layer* Top() { return m_LayerStack.front(); }
		inline Layer* operator[](int index) { return m_LayerStack[index]; }
		inline size_t Size() const { return m_LayerStack.size(); }


		// ---   Iterators   ---
		inline std::deque<Layer*>::iterator begin() noexcept { return m_LayerStack.begin(); }
		inline std::deque<Layer*>::const_iterator begin() const noexcept { return m_LayerStack.begin(); }
		inline std::deque<Layer*>::const_iterator cbegin() const noexcept { return m_LayerStack.cbegin(); }

		inline std::deque<Layer*>::iterator end() noexcept { return m_LayerStack.end(); }
		inline std::deque<Layer*>::const_iterator end() const noexcept { return m_LayerStack.end(); }
		inline std::deque<Layer*>::const_iterator cend() const noexcept { return m_LayerStack.cend(); }

		inline std::deque<Layer*>::reverse_iterator rbegin() noexcept { return m_LayerStack.rbegin(); }
		inline std::deque<Layer*>::const_reverse_iterator rbegin() const noexcept { return m_LayerStack.rbegin(); }
		inline std::deque<Layer*>::const_reverse_iterator crbegin() const noexcept { return m_LayerStack.crbegin(); }

		inline std::deque<Layer*>::reverse_iterator rend() noexcept { return m_LayerStack.rend(); }
		inline std::deque<Layer*>::const_reverse_iterator rend() const noexcept { return m_LayerStack.rend(); }
		inline std::deque<Layer*>::const_reverse_iterator crend() const noexcept { return m_LayerStack.crend(); }

	private:
		std::deque<Layer*> m_LayerStack;
	};

}