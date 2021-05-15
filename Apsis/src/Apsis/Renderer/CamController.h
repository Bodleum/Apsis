#pragma once
#include "Apsis/Event/EventDispatcher.h"
	//#include "Apsis/Core/Core.h"
	//	#include <memory>
	//	#include <chrono>
	//#include "Apsis/Event/Event.h"
	//	#include "Apsis/Core/Input/InputCodes.h"
	//		#include <iostream>
	//#include <map>
	//#include <vector>

namespace A {

	class Cam;

	class CamController : public EventListener
	{
	public:
		CamController(Shared<Cam >cam);
		static void Init(Shared<Cam> cam);

		// Inherited via EventListener
		virtual bool OnEvent(Shared<Event> evt) override;

		static void OnUpdate(std::chrono::microseconds time_step);

	private:
		bool OnMouseScrolled(const MouseWheelEvent& evt);
		bool OnWindowResize(const WindowResizeEvent& evt);

		static Shared<Cam> s_Cam;
		static float s_CamMoveSpeed;

		static Unique<CamController> s_Instance;
	};

}
