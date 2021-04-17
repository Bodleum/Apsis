#include "apch.h"
#include "App.h"

#include "Input.h"

namespace A {

	AppArgs App::m_Args = AppArgs();

	App::App()
		: m_LayerStack()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Created App");
		m_Window = Window::Create(m_Args.MainFnArgs);
	}

	void App::Run()
	{
		AP_PROFILE_FN();

		while (m_Running)
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

	bool App::OnEvent(Event& evt)
	{
		AP_PROFILE_FN();

		switch (evt.GetType())
		{

		case EventType::WindowDestroy:
		{
			m_Running = false;
			break;
		}

		default:
			break;
		}

		return false;
	}

}