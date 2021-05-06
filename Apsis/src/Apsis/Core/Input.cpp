#include "apch.h"
#include "Input.h"

#include "Windows/WindowsInput.h"

namespace A {

	RendererAPI Input::s_RendererAPI = SystemInfo::GetRendererAPI();
	Shared<Input> Input::s_Instance = nullptr;

	const Shared<Input> Input::Create()
	{
		AP_PROFILE_FN();

		s_RendererAPI = SystemInfo::GetRendererAPI();	// Update
		switch (s_RendererAPI)
		{
			case A::RendererAPI::Direct2D:	s_Instance = MakeUnique<WindowsInput>();	break;
			case A::RendererAPI::OpenGL:	s_Instance = MakeUnique<WindowsInput>();	break;
			default:						AP_CRIT_C("Unknown renderer API");			return nullptr;
		}
		Input::Init();
		return s_Instance;
	}

}