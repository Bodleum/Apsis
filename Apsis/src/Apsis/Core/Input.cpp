#include "apch.h"
#include "Input.h"

#include "Windows/WindowsInput.h"

namespace A {

	Unique<Input> Input::s_Instance = Input::Create();

	Unique<Input> Input::Create()
	{
		#if defined(AP_PLATFORM_WIN)
			return MakeUnique<WindowsInput>();
		#else
			return nullptr;
		#endif
	}

}