#pragma once
#include "apch.h"
#include "Apsis/Event/Event.h"

#include <map>
#include <chrono>

namespace A {

	#define BIND_EVT_FN(x) std::bind(&x, this, std::placeholders::_1)

	using NanoSeconds = std::chrono::nanoseconds;

	class Window;
	class EventListener;

	class EventDispatcher
	{
	public:
		static Shared<EventDispatcher> Get();

		static inline void AddListener(EventListener* inst) { s_ListenerList.push_back(inst); }
		static bool DispatchEvent(Shared<Event> evt);
		//template<typename T>
		static void SendEvent(Shared<Event> evt, std::chrono::nanoseconds delay = std::chrono::nanoseconds{ 0 })
		{
			std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> now = std::chrono::system_clock::now();
			s_QueuedEvents.insert({ now + delay, evt });
		}

		static bool PollQueuedEvents();
		static bool PollWindowEvents(Unique<Window>& window);

		EventDispatcher(EventDispatcher const&) = delete;
		EventDispatcher& operator=(EventDispatcher const&) = delete;

	private:
		EventDispatcher() {}

		static std::vector<EventListener*> s_ListenerList;
		static std::map<std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>, Shared<Event>> s_QueuedEvents;
	};

	class EventListener
	{
		friend class EventDispatcher;
	protected:
		virtual bool OnEvent(Shared<Event> evt) = 0;
		EventListener() { EventDispatcher::AddListener(this); }
	};

	class LocalDispatcher
	{
	public:
		LocalDispatcher(Shared<Event> evt) : m_Event(evt) { }//EventDispatcher::AddListener(this); }

		template<typename T, typename F>
		bool Dispatch(const F& fn)
		{
			if (m_Event->GetType() == T::GetTypeS())
			{
				m_Event->m_Complete = fn((T&)(*m_Event));
				return true;
			}
			return false;
		}

	private:
		Shared<Event> m_Event;
	};


}