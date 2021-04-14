#include "apch.h"
#include "App.h"

namespace A {

	App::App(AppArgs args)
		: m_Args(args), m_LayerStack()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Created App");
		m_Window = Window::Create(args.MainFnArgs);
	}

	void App::Run()
	{
		AP_PROFILE_FN();

		while (true)
		{
			OnUpdate();
		}
	}

	void App::OnUpdate()
	{
		AP_PROFILE_FN();

		m_Window->PollEvents();

		// Update each layer if enabled
		for (Layer* layer : m_LayerStack)
			if (layer->IsEnabled())
				layer->OnUpdate();
	}

	void App::PushLayer(Layer* layer)
	{
		AP_PROFILE_FN();
		m_LayerStack.Push(layer);
		layer->OnAdd();
	}

	void App::EmlpaceLayer(Layer* layer)
	{
		AP_PROFILE_FN();
		m_LayerStack.Emplace(layer);
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