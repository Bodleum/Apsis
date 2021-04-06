#include "apch.h"
#include "App.h"

namespace A {

	App::App()
	{
		AP_PROFILE_FN();

		AP_INFO_C("Created App");
		this->LogInfo();
	}

	void App::Run()
	{
		AP_PROFILE_FN();
	}

	void App::LogInfo()
	{
		AP_PROFILE_FN();

		if (A::Platform::Windows)
			AP_INFO_C("Platform: Windows (x64)");
		else if (A::Platform::Simulator)
			AP_INFO_C("Platform: Simulator");
		else if (A::Platform::iPhone)
			AP_INFO_C("Platform: iPhone");
		else if (A::Platform::OSX)
			AP_INFO_C("Platform: OSX");
		else if (A::Platform::Linux)
			AP_INFO_C("Platform: Linux");
		else if (A::Platform::Unix)
			AP_INFO_C("Platform: Unix");
		else if (A::Platform::POSIX)
			AP_INFO_C("Platform: POSIX");
		else
			AP_INFO_C("Platform: Unknown");
	}

}