#pragma once
#include "Apsis/Core/Layer.h"
//#include "Apsis/Core/Main.h"				Included in Window.h
#include "Apsis/Core/Window.h"
//#include "Apsis/Event/Event.h"			Included in EventDispatcher.h
//#include "Apsis/Event/EventDispatcher.h"	Included in Layer.h
#include "Apsis/Renderer/Cam.h"

//#include <chrono>							Included in EventDispacher.h

namespace A {

	using MicroSeconds = std::chrono::microseconds;

	class Renderer;

	class App : public EventListener
	{
	public:
		App();
		virtual ~App() = default;
		static inline App* Get() { return s_Instance; }
		inline const Unique<Window>& GetWindow() { return m_Window; }

		bool PollEvents();
		void OnUpdate(MicroSeconds time_step);
		void OnRender();
		// Inherited via EventListener
		virtual bool OnEvent(Shared<Event> evt) override;

		void CreateCam(CamType cam_type);
		void PushLayer(Layer* layer);
		void EmlpaceLayer(Layer* layer);
		void PopLayer();

		inline void SetTimeStep(std::chrono::microseconds new_time_step) { m_TimeStep = new_time_step; }

	private:
		void Run();

		static inline void SetAppArgs(AppArgs args) { m_Args = args; }

		#ifdef AP_PLATFORM_WIN
			friend int WINAPI ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd);
		#else
			friend int ::main(int argc, char** argv);
		#endif // AP_PLATFORM_WIN

		bool m_Running = true;
		static AppArgs m_Args;
		static App* s_Instance;
		// Assets
		LayerStack m_LayerStack;
		Unique<Window> m_Window;
		Shared<Renderer> m_Renderer;
		Shared<Cam> m_Cam = nullptr;
		// Timing
		MicroSeconds m_TimeStep{ 16667 };	// 60ups by default
		MicroSeconds m_TimeAccumulator{ 0 };
		MicroSeconds m_FrameTime{ 0 };
		std::chrono::time_point<std::chrono::steady_clock, MicroSeconds> m_CurrentTime;
		std::chrono::time_point<std::chrono::steady_clock, MicroSeconds> m_NewTime;
	};

	// Defined in client code
	App* CreateApp();

}