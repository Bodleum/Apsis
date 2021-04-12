#include "apch.h"
#include "App.h"

namespace A {

	App::App()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Created App");
	}

	void App::Run()
	{
		AP_PROFILE_FN();
	}

	void App::OnUpdate()
	{
		AP_PROFILE_FN();

		for (int i = 0; i < m_LayerStack.Size(); i++)
		{
			// Update each layer if enabled
			if (m_LayerStack[i]->IsEnabled())
				m_LayerStack[i]->OnUpdate();
		}
	}

	void App::PushLayer(Layer* layer)
	{
		AP_PROFILE_FN();
		m_LayerStack.Push(layer);
		layer->OnAdd();
	}

	void App::PopLayer()
	{
		AP_PROFILE_FN();
		m_LayerStack[0]->OnRemove();
		m_LayerStack.Pop();
	}

	void App::LogInfo()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Platform: {0}", SystemInfo::Platform);

	}

}