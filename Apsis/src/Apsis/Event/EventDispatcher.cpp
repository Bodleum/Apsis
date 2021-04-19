#include "apch.h"
#include "EventDispatcher.h"

#include "Apsis/Core/Window.h"

namespace A {

	std::vector<EventListener*> EventDispatcher::s_ListenerList = {};

	Shared<EventDispatcher> EventDispatcher::Get()
	{
		AP_PROFILE_FN();
		static Shared<EventDispatcher> instance{};
		return instance;
	}

	bool EventDispatcher::DispatchEvent(Event& evt)
	{
		AP_PROFILE_FN();

		bool eventComleted = false;
		for (auto &listener : s_ListenerList)
			if (listener->OnEvent(evt))
			{
				eventComleted = true;
				break;
			}

		return eventComleted;
	}

	bool EventDispatcher::PollWindowEvents(Unique<Window>& window)
	{
		return window->PollEvents();
	}

}