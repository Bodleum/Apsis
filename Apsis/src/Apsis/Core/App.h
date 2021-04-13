#pragma once
#include "Apsis/Core/Layer.h"
#include "Apsis/Core/Main.h"
//#include "Apsis/Event/Event.h"		Included in EventListener.h
#include "Apsis/Event/EventListener.h"

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

		#ifdef AP_PLATFORM_WIN
			friend int WINAPI ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd);
		#else
			friend int ::main(int argc, char** argv);
		#endif // AP_PLATFORM_WIN

		LayerStack m_LayerStack;

	};

	// Defined in client code
	App* CreateApp();

}