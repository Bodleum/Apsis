#include "apch.h"
#include "EventDispatcher.h"

#include "Apsis/Core/Window.h"

namespace A {

	std::vector<EventListener*> EventDispatcher::s_ListenerList = {};
	std::map<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>, Shared<Event>> EventDispatcher::s_QueuedEvents = {};

	Shared<EventDispatcher> EventDispatcher::Get()
	{
		AP_PROFILE_FN();
		static Shared<EventDispatcher> instance{};
		return instance;
	}

	bool EventDispatcher::DispatchEvent(Shared<Event> evt)
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

	//void EventDispatcher::SendEvent(Event& evt, std::chrono::nanoseconds delay)
	//{
	//	std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> now = std::chrono::system_clock::now();
	//	s_QueuedEvents.insert({ now + delay, evt });
	//}

	bool EventDispatcher::PollQueuedEvents()
	{
		bool eventsExist = false;
		std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> now = std::chrono::system_clock::now();

		auto it = s_QueuedEvents.begin();
		while (it != s_QueuedEvents.end())
		{
			if (it->first <= now)
			{
				eventsExist = true;
				EventDispatcher::DispatchEvent(it->second);
				it = s_QueuedEvents.erase(it);
			}
			else
				break;
		}

		return eventsExist;
	}

	bool EventDispatcher::PollWindowEvents(Unique<Window>& window)
	{
		return window->PollEvents();
	}

}