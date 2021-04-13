#include "apch.h"
#include "App.h"

namespace A {

	App::App(AppArgs* args)
		: m_Args(args)
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

		// Update each layer if enabled
		for (Layer* layer : m_LayerStack)
			if (layer->IsEnabled())
				layer->OnAdd();
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
		m_LayerStack.Top()->OnRemove();
		m_LayerStack.Pop();
	}

	void App::LogInfo()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Platform: {0}", SystemInfo::Platform);
	}

	void App::OnEvent(Event& evt)
	{
		AP_PROFILE_FN();
	}

}