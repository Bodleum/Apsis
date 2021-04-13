#pragma once
#include "Apsis/Event/Event.h"

namespace A {

	class EventListener
	{
	protected:
		virtual void OnEvent(Event& evt) = 0;
	};

}