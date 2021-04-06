#include "apch.h"
#include "Main.h"

#include "Apsis/Core/App.h"


extern A::Application* A::CreateApplication();

int main(int argc, char** argv)
{
	auto app = A::CreateApplication();

	app->Run();

	delete app;
	return 0;
}
