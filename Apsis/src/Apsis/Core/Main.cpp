#include "apch.h"
#include "Main.h"

#include "Apsis/Core/App.h"
#include "Apsis/Core/Logger.h"


extern A::App* A::CreateApp();

int main(int argc, char** argv)
{
	AP_PROFILE_BEGIN_SESSION("Startup", "Apsis - Startup.json");
		A::Logger::Init();
		auto app = A::CreateApp();
	AP_PROFILE_END_SESSION();

	AP_PROFILE_BEGIN_SESSION("Runtime", "Apsis - Runtime.json");
		app->Run();
	AP_PROFILE_END_SESSION();

	AP_PROFILE_BEGIN_SESSION("Shutdown", "Apsis - Shutdown.json");
		delete app;
	AP_PROFILE_END_SESSION();

	return 0;
}
