#include "apch.h"
#include "Input.h"

#include "Windows/WindowsInput.h"

namespace A {

	Shared<Input> Input::s_Instance = nullptr;

	Shared<Input> Input::Create()
	{
		if (s_Instance)
			return s_Instance;

		#if defined(AP_PLATFORM_WIN)
			return MakeShared<WindowsInput>();
		#else
			AP_CRIT_C("Platform not supported");
		#endif
	}

}