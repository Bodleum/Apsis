#pragma once

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
		bool m_Enabled;
	};

}