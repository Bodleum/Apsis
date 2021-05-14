#include "apch.h"
#include "EventDispatcher.h"
	//#include "Apsis/Core/Core.h"
	//	#include <memory>
	//	#include <chrono>
	//#include "Apsis/Event/Event.h"
	//	#include "Apsis/Core/Input/InputCodes.h"
	//		#include <iostream>
	//#include <map>
	//#include <vector>

#include "Apsis/Core/Window.h"

namespace A {

	std::vector<EventListener*> EventDispatcher::s_ListenerList = {};
	std::map<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>, Shared<Event>> EventDispatcher::s_QueuedEvents = {};

	bool EventDispatcher::SendBlockingEvent(Shared<Event> evt)
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

	void EventDispatcher::SendEvent(Shared<Event> evt, std::chrono::milliseconds delay)
	{
		AP_PROFILE_FN();
		std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> now = std::chrono::system_clock::now();
		s_QueuedEvents.insert({ now + delay, evt });
	}

	bool EventDispatcher::PollQueuedEvents()
	{
		AP_PROFILE_FN();

		bool eventRes = false;
		std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> now = std::chrono::system_clock::now();

		auto it = s_QueuedEvents.begin();
		while (it != s_QueuedEvents.end() && it->first <= now)
		{
			eventRes = EventDispatcher::SendBlockingEvent(it->second);
			it = s_QueuedEvents.erase(it);
		}

		return eventRes;
	}

	bool EventDispatcher::PollWindowEvents(Unique<Window>& window)
	{
		AP_PROFILE_FN();
		return window->PollEvents();
	}

}