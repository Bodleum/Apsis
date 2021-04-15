#pragma once
#include "Apsis/Core/Layer.h"
#include "Apsis/Core/Main.h"
#include "Apsis/Core/Window.h"
//#include "Apsis/Event/Event.h"		Included in EventDispatcher.h
#include "Apsis/Event/EventDispatcher.h"

namespace A {

	class App : public EventListener
	{
	public:
		App(AppArgs args);
		virtual ~App() = default;

		void OnUpdate();
		// Inherited via EventListener
		virtual bool OnEvent(Event& evt) override;

		void PushLayer(Layer* layer);
		void EmlpaceLayer(Layer* layer);
		void PopLayer();

	private:
		void Run();

		static void LogInfo();

		#ifdef AP_PLATFORM_WIN
			friend int WINAPI ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd);
		#else
			friend int ::main(int argc, char** argv);
		#endif // AP_PLATFORM_WIN

		AppArgs m_Args;
		LayerStack m_LayerStack;
		Unique<Window> m_Window;

	};

	// Defined in client code
	App* CreateApp(AppArgs args);

}