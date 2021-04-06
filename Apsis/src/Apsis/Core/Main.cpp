#include "apch.h"
#include "Main.h"

#include "Apsis/Core/App.h"
#include "Apsis/Core/Logger.h"


extern A::App* A::CreateApp();

int main(int argc, char** argv)
{
	A::Logger::Init();

	auto app = A::CreateApp();

	app->Run();

	delete app;
	return 0;
}
