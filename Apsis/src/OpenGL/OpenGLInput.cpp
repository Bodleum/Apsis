#include "apch.h"
#include "OpenGLInput.h"

#include "Apsis/Core/App.h"
#include "Translators.h"
#include "OpenGLHeaders.h"

namespace A {

	void OpenGlInput::InitImpl()
	{
		AP_PROFILE_FN();
		m_WindowHandle = (GLFWwindow*)App::Get()->GetWindow()->GetHandle();
	}

	bool OpenGlInput::IsKeyDownImpl(KeyCode key_code)
	{
		AP_PROFILE_FN();
		return glfwGetKey(m_WindowHandle, KeyCodeToGLFWKeyCodeTranslator[key_code]) == GLFW_PRESS;
	}

	bool OpenGlInput::WasKeyDownImpl(KeyCode key_code)
	{
		AP_PROFILE_FN();
		AP_ERROR_C("WasKeyDown is not supported in OpenGL");
		return false;
	}

	bool OpenGlInput::IsMouseButtonDownImpl(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		return glfwGetKey(m_WindowHandle, MouseCodeToGLFWMouseButtonTranslator[mouse_code]) == GLFW_PRESS;
	}

	bool OpenGlInput::WasMouseButtonDownImpl(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		AP_ERROR_C("WasMouseButtonDown is not supported in OpenGL");
		return false;
	}

	std::array<int, 2> OpenGlInput::GetMousePosImpl()
	{
		AP_PROFILE_FN();
		double x, y;
		glfwGetCursorPos(m_WindowHandle, &x, &y);
		return std::array<int, 2>({ (int)x, (int)y });
	}

	int OpenGlInput::GetMouseXImpl()
	{
		AP_PROFILE_FN();
		return GetMousePosImpl()[0];
	}

	int OpenGlInput::GetMouseYImpl()
	{
		AP_PROFILE_FN();
		return GetMousePosImpl()[1];
	}

}