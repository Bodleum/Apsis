#include "apch.h"
#include "Main.h"

#include "Apsis/Core/App.h"


extern A::App* A::CreateApp();

int main(int argc, char** argv)
{
	auto app = A::CreateApp();

	app->Run();

	delete app;
	return 0;
}
