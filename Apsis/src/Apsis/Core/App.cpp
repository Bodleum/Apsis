#include "apch.h"
#include "App.h"
	//#include "Apsis/Core/Layer.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//	#include <deque>
	//#include "Apsis/Event/EventDispatcher.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//	#include "Apsis/Event/Event.h"
	//		#include "Apsis/Core/Input/InputCodes.h"
	//			#include <iostream>
	//	#include <map>
	//	#include <vector>
	//#include "Apsis/Core/Window.h"
	//#include "Apsis/Renderer/Cam.h"
	//	#include <Eigen/Core>
	//	#include <Eigen/Geometry>
	//	#include <Eigen/Dense>

#include "Apsis/Core/Input/Input.h"
	//#include "Apsis/Core/Input/InputCodes.h"
	//	#include <iostream>
#include "Apsis/Core/Main.h"
#include "Apsis/Renderer/CamController.h"
	//#include "Apsis/Event/EventDispatcher.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//	#include "Apsis/Event/Event.h"
	//		#include "Apsis/Core/Input/InputCodes.h"
	//			#include <iostream>
	//	#include <map>
	//	#include <vector>
#include "Apsis/Renderer/Renderer.h"
	//#include "Apsis/Core/SystemInfo.h"
	//#include "Apsis/Renderer/Cam.h"
	//	#include <Eigen/Core>
	//	#include <Eigen/Geometry>
	//	#include <Eigen/Dense>
	//#include "Apsis/Renderer/Shader.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//#include "Apsis/Renderer/Texture.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>

namespace A {

	App* App::s_Instance = nullptr;
	AppArgs App::s_Args = AppArgs();

	App::App()
		: m_Window(Window::Create(s_Args.MainFnArgs)), m_Renderer(Renderer::Create(m_Window)), m_CurrentTime(std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()))
	{
		AP_PROFILE_FN();

		s_Instance = this,
		AP_INFO_C("Created App");
	}

	void App::Run()
	{
		AP_PROFILE_FN();

		if (!m_Cam)
			AP_CRIT_C("No camera set up, use A::App::CreateCam(A::CamType cam_type)");

		while (m_Running)
		{
			m_NewTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now());	// Get new time
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

			OnRender();
			PollEvents();
		}
	}

	void App::SetAppArgs(AppArgs args) { s_Args = args; }

	bool App::PollEvents()
	{
		AP_PROFILE_FN();
		bool windowRes = EventDispatcher::PollWindowEvents(m_Window);
		bool queueRes = EventDispatcher::PollQueuedEvents();
		return queueRes || windowRes;
	}

	void App::OnUpdate(std::chrono::microseconds time_step)
	{
		AP_PROFILE_FN();
		// Update CamController
		CamController::OnUpdate(time_step);
		// Update each layer if enabled
		for (Layer* layer : m_LayerStack)
			if (layer->IsEnabled())
				layer->OnUpdate(time_step);


		//m_Cam->Rotate(0.5f);
	}

	void App::OnRender()
	{
		AP_PROFILE_FN();
		Renderer::BeginDraw(m_Cam);
		Renderer::Clear();
		// Render each layer from the bottom up
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
			if ((*it)->IsEnabled())
				(*it)->OnRender();
		Renderer::EndDraw();
	}

	void App::CreateCam(CamType cam_type)
	{
		AP_PROFILE_FN();

		float width = m_Window->GetWidth();
		float aspectRatio = (float)m_Window->GetWidth() / (float)m_Window->GetHeight();

		switch (cam_type)
		{
			case A::CamType::Ortho:
				m_Cam = MakeShared<OrthoCam>(-aspectRatio, aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
				break;
			default:
				break;
		}

		CamController::Init(m_Cam);
	}

	void App::PushLayer(Layer* layer)
	{
		AP_PROFILE_FN();
		m_LayerStack.Push(layer);
		layer->OnAddBackend();
	}

	void App::EmlpaceLayer(Layer* layer)
	{
		AP_PROFILE_FN();
		m_LayerStack.Emplace(layer);
		layer->OnAddBackend();
	}

	void App::PopLayer()
	{
		AP_PROFILE_FN();
		m_LayerStack.Top()->OnRemoveBackend();
		m_LayerStack.Pop();
	}

	bool App::OnEvent(Shared<Event> evt)
	{
		AP_PROFILE_FN();

		LocalDispatcher ld(evt);
		ld.Dispatch<WindowResizeEvent>(BIND_EVT_FN(App::OnWindowResize));

		switch (evt->GetType())
		{
			case EventType::WindowPaint:	OnRender();					break;
			case EventType::WindowDestroy:	m_Window.reset(nullptr);	break;
			case EventType::AppQuit:		m_Running = false;			return true;
			default:													break;


			case EventType::MouseButtonDown: m_Cam->SetOrientation(0.0f);	break;
		}

		for (Layer* layer : m_LayerStack)
			if (layer->OnEvent(evt))
				return true;

		return false;
	}

	bool App::OnWindowResize(const WindowResizeEvent& evt)
	{
		AP_PROFILE_FN();
		Renderer::OnResize(evt);
		return false;
	}

}