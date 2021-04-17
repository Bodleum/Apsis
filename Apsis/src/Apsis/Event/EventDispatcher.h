#pragma once
#include "apch.h"
#include "Apsis/Event/Event.h"

namespace A {

	class EventListener;

	class EventDispatcher
	{
	public:
		static Shared<EventDispatcher> Get();

		static inline void AddListener(EventListener* inst) { s_ListenerList.push_back(inst); }
		static bool DispatchEvent(Event& evt);

		EventDispatcher(EventDispatcher const&) = delete;
		EventDispatcher& operator=(EventDispatcher const&) = delete;

	private:
		EventDispatcher() {}

		static std::vector<EventListener*> EventDispatcher::s_ListenerList;
	};

	class EventListener
	{
		friend class EventDispatcher;
	protected:
		virtual bool OnEvent(Event& evt) = 0;
		EventListener() { EventDispatcher::AddListener(this); }
	};


}