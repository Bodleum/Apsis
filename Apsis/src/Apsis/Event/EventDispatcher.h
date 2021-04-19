#pragma once
#include "apch.h"
#include "Apsis/Event/Event.h"

namespace A {

	#define BIND_EVT_FN(x) std::bind(&x, this, std::placeholders::_1)

	class Window;
	class EventListener;

	class EventDispatcher
	{
	public:
		static Shared<EventDispatcher> Get();

		static inline void AddListener(EventListener* inst) { s_ListenerList.push_back(inst); }
		static bool DispatchEvent(Event& evt);

		static bool PollWindowEvents(Unique<Window>& window);

		EventDispatcher(EventDispatcher const&) = delete;
		EventDispatcher& operator=(EventDispatcher const&) = delete;

	private:
		EventDispatcher() {}

		static std::vector<EventListener*> s_ListenerList;
	};

	class EventListener
	{
		friend class EventDispatcher;
	protected:
		virtual bool OnEvent(Event& evt) = 0;
		EventListener() { EventDispatcher::AddListener(this); }
	};

	class LocalDispatcher
	{
	public:
		LocalDispatcher(Event& evt) : m_Event(evt) { }//EventDispatcher::AddListener(this); }

		template<typename T, typename F>
		bool Dispatch(const F& fn)
		{
			if (m_Event.GetType() == T::GetTypeS())
			{
				m_Event.m_Complete = fn((T&)(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};


}