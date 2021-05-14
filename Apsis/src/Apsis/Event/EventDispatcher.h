#pragma once
#include "Apsis/Core/Core.h"
	//#include <memory>
	//#include <chrono>
#include "Apsis/Event/Event.h"
	//#include "Apsis/Core/Input/InputCodes.h"
	//	#include <iostream>

#include <map>
#include <vector>

namespace A {

	#define BIND_EVT_FN(x) std::bind(&x, this, std::placeholders::_1)

	class Window;
	class EventListener;

	class EventDispatcher
	{
	public:
		static inline void AddListener(EventListener* inst) { s_ListenerList.push_back(inst); }
		static bool SendBlockingEvent(Shared<Event> evt);
		static void SendEvent(Shared<Event> evt, std::chrono::milliseconds delay = std::chrono::milliseconds{ 0 });
		inline static void SendMsg(const char* message, std::chrono::milliseconds delay = std::chrono::milliseconds{ 0 }) { SendEvent(MakeShared<Message>(message), delay); }
		inline static bool SendBlockingMessage(const char* message) { return SendBlockingEvent(MakeShared<Message>(message)); }

		static bool PollQueuedEvents();
		static bool PollWindowEvents(Unique<Window>& window);

	private:
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