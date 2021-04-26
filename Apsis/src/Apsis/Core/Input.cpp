#include "apch.h"
#include "Input.h"

#include "Windows/WindowsInput.h"

namespace A {

	Unique<Input> Input::s_Instance = nullptr;

	Unique<Input>& Input::Create()
	{
		AP_PROFILE_FN();
		#if defined(AP_PLATFORM_WIN)
			s_Instance = MakeUnique<WindowsInput>();
			return s_Instance;
		#else
			return nullptr;
		#endif
	}

}