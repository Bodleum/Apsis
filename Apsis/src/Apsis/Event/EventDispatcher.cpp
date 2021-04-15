#include "apch.h"
#include "EventDispatcher.h"

namespace A {

	std::vector<EventListener*> EventDispatcher::s_ListenerList = {};

	Shared<EventDispatcher> EventDispatcher::Get()
	{
		AP_PROFILE_FN();
		static Shared<EventDispatcher> instance{};
		return instance;
	}

	bool EventDispatcher::OnEvent(Event& evt)
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

}