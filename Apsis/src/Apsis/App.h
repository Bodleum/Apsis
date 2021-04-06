#pragma once

int main(int argc, char** argv);

namespace A {

	class Application
	{
	public:
		Application() {};
		virtual ~Application() {};

	private:
		void Run();

		friend int ::main(int argc, char** argv);
	};

	// Defined in client code
	Application* CreateApplication();

}