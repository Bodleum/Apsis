#include "apch.h"
#include "App.h"

#include "Input.h"

namespace A {

	AppArgs App::m_Args = AppArgs();

	App::App()
		: m_LayerStack(), m_CurrentTime(std::chrono::time_point_cast<MicroSeconds>(std::chrono::steady_clock::now()))
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
			m_NewTime = std::chrono::time_point_cast<MicroSeconds>(std::chrono::steady_clock::now());	// Get new time
			m_FrameTime = (m_NewTime - m_CurrentTime);	// Calcultate frame time
			if (m_FrameTime > 25 * m_TimeStep)	// Clipping
				m_FrameTime = 25 * m_TimeStep;
			m_CurrentTime = m_NewTime;	// Set current time to start timing the frame we're about to process
			m_TimeAccumulator += m_FrameTime;	// Add frame time to the accumulator

			// Do updates
			while (m_TimeAccumulator >= m_TimeStep)
			{
				OnUpdate(m_TimeStep);
				m_TimeAccumulator -= m_TimeStep;
			}

			/* Interpolate rendering
			const auto alpha = m_TimeAccumulator / m_TimeStep;
			* 
			* Some other stuff
			* See: https://gafferongames.com/post/fix_your_timestep/
			*/

			// OnRender();
		}
	}

	void App::OnUpdate(MicroSeconds time_step)
	{
		AP_PROFILE_FN();

		m_Window->PollEvents();

		// Update each layer if enabled
		for (Layer* layer : m_LayerStack)
			if (layer->IsEnabled())
				layer->OnUpdate(time_step);
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

		for (Layer* layer : m_LayerStack)
		{
			if (layer->OnEvent(evt))
				return true;
		}

		return false;
	}

}