#include "apch.h"
#include "Input.h"

#include "Windows/WindowsInput.h"

namespace A {

	PlatformType Input::s_Platform;
	Shared<Input> Input::s_Instance = nullptr;

	const Shared<Input> Input::Create()
	{
		AP_PROFILE_FN();

		s_Platform = SystemInfo::GetPlatform();
		switch (s_Platform)
		{
			case Platform::Windows:	s_Instance = MakeUnique<WindowsInput>();	break;
			default:						AP_CRIT_C("Unknown platform");			return nullptr;
		}
		Input::Init();
		return s_Instance;
	}

}