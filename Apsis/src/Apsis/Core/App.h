#pragma once
#include "Apsis/Core/Layer.h"
//#include "Apsis/Core/Main.h"				Included in Window.h
#include "Apsis/Core/Window.h"
//#include "Apsis/Event/Event.h"			Included in EventDispatcher.h
//#include "Apsis/Event/EventDispatcher.h"	Included in Layer.h

namespace A {

	class App : public EventListener
	{
	public:
		App();
		virtual ~App() = default;

		void OnUpdate();
		// Inherited via EventListener
		virtual bool OnEvent(Event& evt) override;

		void PushLayer(Layer* layer);
		void EmlpaceLayer(Layer* layer);
		void PopLayer();

	private:
		void Run();

		static inline void SetAppArgs(AppArgs args) { m_Args = args; }
		static void LogInfo();

		#ifdef AP_PLATFORM_WIN
			friend int WINAPI ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd);
		#else
			friend int ::main(int argc, char** argv);
		#endif // AP_PLATFORM_WIN

		bool m_Running = true;
		static AppArgs m_Args;
		LayerStack m_LayerStack;
		Unique<Window> m_Window;

	};

	// Defined in client code
	App* CreateApp();

}