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

	private:
		bool OnMouseScrolled(const MouseWheelEvent& evt);
		bool OnWindowResize(const WindowResizeEvent& evt);

		Shared<Cam> m_Cam = nullptr;

		static Unique<CamController> s_Instance;
	};

}
