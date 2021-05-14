#pragma once
#include "Apsis/Core/Layer.h"
	//#include "Apsis/Core/Core.h"
	//	#include <memory>
	//	#include <chrono>
	//#include <deque>
#include "Apsis/Event/EventDispatcher.h"
	//#include "Apsis/Core/Core.h"
	//	#include <memory>
	//	#include <chrono>
	//#include "Apsis/Event/Event.h"
	//	#include "Apsis/Core/Input/InputCodes.h"
	//		#include <iostream>
	//#include <map>
	//#include <vector>


//#include "Apsis/Core/Main.h"				Included in Window.h
#include "Apsis/Core/Window.h"
#include "Apsis/Renderer/Cam.h"


namespace A {

	class Renderer;

	class App : public EventListener
	{
	public:
		App();
		virtual ~App() = default;
		static inline App* Get() { return s_Instance; }
		inline const Unique<Window>& GetWindow() { return m_Window; }

		bool PollEvents();
		void OnUpdate(std::chrono::microseconds time_step);
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

		static inline void SetAppArgs(AppArgs args) { s_Args = args; }

		#ifdef AP_PLATFORM_WIN
			friend int WINAPI ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd);
		#else
			friend int ::main(int argc, char** argv);
		#endif // AP_PLATFORM_WIN

		bool m_Running = true;
		static AppArgs s_Args;
		static App* s_Instance;
		// Assets
		LayerStack m_LayerStack = LayerStack();
		Unique<Window> m_Window = nullptr;
		Shared<Renderer> m_Renderer = nullptr;
		Shared<Cam> m_Cam = nullptr;
		// Timing
		std::chrono::microseconds m_TimeStep{ 16667 };	// 60ups by default
		std::chrono::microseconds m_TimeAccumulator{ 0 };
		std::chrono::microseconds m_FrameTime{ 0 };
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> m_CurrentTime;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::microseconds> m_NewTime;



		float m_Angle = 0.0f;
	};

	// Defined in client code
	App* CreateApp();

}