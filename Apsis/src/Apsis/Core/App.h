#pragma once
#include "Apsis/Core/Layer.h"

int main(int argc, char** argv);

namespace A {

	class App
	{
	public:
		App();
		virtual ~App() = default;

		void OnUpdate();

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