#pragma once

int main(int argc, char** argv);

namespace A {

	class App
	{
	public:
		App();
		virtual ~App() = default;

	private:
		void Run();
		static void LogInfo();

		friend int ::main(int argc, char** argv);
	};

	// Defined in client code
	App* CreateApp();

}