#pragma once
#include "Apsis/Core/Layer.h"
//#include "Apsis/Event/Event.h"		Included in EventListener.h
#include "Apsis/Event/EventListener.h"

int main(int argc, char** argv);

namespace A {

	class App : public EventListener
	{
	public:
		App();
		virtual ~App() = default;

		void OnUpdate();
		// Inherited via EventListener
		virtual void OnEvent(Event& evt) override;

		void PushLayer(Layer* layer);
		void PopLayer();

	private:
		void Run();

		static void LogInfo();

		friend int ::main(int argc, char** argv);

		LayerStack m_LayerStack;

	};

	// Defined in client code
	App* CreateApp();

}