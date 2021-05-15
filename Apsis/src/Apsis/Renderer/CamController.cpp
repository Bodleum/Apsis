#include "apch.h"
#include "CamController.h"
	//#include "Apsis/Event/EventDispatcher.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//	#include "Apsis/Event/Event.h"
	//		#include "Apsis/Core/Input/InputCodes.h"
	//			#include <iostream>
	//	#include <map>
	//	#include <vector>

#include "Apsis/Renderer/Cam.h"
	//#include <Eigen/Core>
	//#include <Eigen/Geometry>
	//#include <Eigen/Dense>
#include "Apsis/Core/Input/Input.h"
	//#include "Apsis/Core/Input/InputCodes.h"
	//	#include <iostream>

namespace A {

	Shared<Cam> CamController::s_Cam = nullptr;
	float CamController::s_CamMoveSpeed = 1.0f;
	Unique<CamController> CamController::s_Instance = nullptr;

	CamController::CamController(Shared<Cam> cam)
	{
		s_Cam = cam;
	}

	void CamController::Init(Shared<Cam> cam)
	{
		if (s_Instance)
		{
			AP_WARN_C("CamController already exists");
			return;
		}
		s_Instance = MakeUnique<CamController>(cam);
	}

	bool CamController::OnEvent(Shared<Event> evt)
	{
		LocalDispatcher ld(evt);

		ld.Dispatch<MouseWheelEvent>(BIND_EVT_FN(CamController::OnMouseScrolled));
		ld.Dispatch<WindowResizeEvent>(BIND_EVT_FN(CamController::OnWindowResize));

		return false;
	}

	void CamController::OnUpdate(std::chrono::microseconds time_step)
	{
		AP_PROFILE_FN();

		if (Input::IsKeyDown(Key::H))
			s_Cam->Move(Eigen::Vector3f(-s_CamMoveSpeed * std::chrono::duration_cast<std::chrono::milliseconds>(time_step).count() * 0.001f, 0.0f, 0.0f));
		if (Input::IsKeyDown(Key::N))
			s_Cam->Move(Eigen::Vector3f(s_CamMoveSpeed * std::chrono::duration_cast<std::chrono::milliseconds>(time_step).count() * 0.001f, 0.0f, 0.0f));

		if (Input::IsKeyDown(Key::C))
			s_Cam->Move(Eigen::Vector3f(0.0f, s_CamMoveSpeed * std::chrono::duration_cast<std::chrono::milliseconds>(time_step).count() * 0.001f, 0.0f));
		if (Input::IsKeyDown(Key::T))
			s_Cam->Move(Eigen::Vector3f(0.0f, -s_CamMoveSpeed * std::chrono::duration_cast<std::chrono::milliseconds>(time_step).count() * 0.001f, 0.0f));

		if (Input::IsKeyDown(Key::G))
			s_Cam->Rotate(5.0f);
		if (Input::IsKeyDown(Key::R))
			s_Cam->Rotate(-5.0f);
	}

	bool CamController::OnMouseScrolled(const MouseWheelEvent& evt)
	{
		float zoom = evt.GetDelta() * 0.1f;
		s_Cam->Zoom(zoom);
		return false;
	}

	bool CamController::OnWindowResize(const WindowResizeEvent& evt)
	{
		float aspectRatio = (float)evt.GetWidth() / (float)evt.GetHeight();
		s_Cam->SetProj(-aspectRatio * s_Cam->GetZoom(), aspectRatio * s_Cam->GetZoom(), -1.0f * s_Cam->GetZoom(), s_Cam->GetZoom(), -1.0f, 1.0f);
		return false;
	}

}