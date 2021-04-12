#include "apch.h"
#include "Layer.h"

namespace A {

	Layer::Layer()
		: m_Enabled(false)
	{
	}

	void Layer::OnAdd()
	{
		m_Enabled = true;
	}

	void Layer::OnRemove()
	{
		m_Enabled = false;
	}

}