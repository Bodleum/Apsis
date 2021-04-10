#include "apch.h"
#include "App.h"

namespace A {

	App::App()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Created App");
	}

	void App::Run()
	{
		AP_PROFILE_FN();
	}

	void App::LogInfo()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Platform: {0}", SystemInfo::Platform);

	}

}