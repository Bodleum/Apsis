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

namespace A {

	Unique<CamController> CamController::s_Instance = nullptr;

	CamController::CamController(Shared<Cam> cam)
		: m_Cam(cam)
	{
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

	bool CamController::OnMouseScrolled(const MouseWheelEvent& evt)
	{
		float zoom = evt.GetDelta() * 0.1f;
		m_Cam->Zoom(zoom);

		std::cout << m_Cam->GetVP().matrix() << std::endl << std::endl;
		return false;
	}

	bool CamController::OnWindowResize(const WindowResizeEvent& evt)
	{
		float aspectRatio = (float)evt.GetWidth() / (float)evt.GetHeight();
		m_Cam->SetProj(-aspectRatio * m_Cam->GetZoom(), aspectRatio * m_Cam->GetZoom(), -1.0f * m_Cam->GetZoom(), m_Cam->GetZoom(), -1.0f, 1.0f);
		return false;
	}

}