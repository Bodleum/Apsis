#include "apch.h"
#include "Apsis/Core/Input/Input.h"
	//#include "Apsis/Core/Input/InputCodes.h"
	//	#include <iostream>

#include "Apsis/Core/App.h"
	//#include "Apsis/Core/Layer.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//	#include <deque>
	//#include "Apsis/Event/EventDispatcher.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//	#include "Apsis/Event/Event.h"
	//		#include "Apsis/Core/Input/InputCodes.h"
	//			#include <iostream>
	//	#include <map>
	//	#include <vector>
	//#include "Apsis/Core/Window.h"
	//#include "Apsis/Renderer/Cam.h"
	//	#include <Eigen/Core>
	//	#include <Eigen/Geometry>
	//	#include <Eigen/Dense>
#include "Translators.h"
	//#include "Apsis/Core/Input/InputCodes.h"
	//	#include <iostream>
#include "Headers.h"
	//#include <glad/glad.h>
	//#include <GLFW/glfw3.h>

namespace A {
	
	//static GLFWwindow* ls_WindowHandle = (GLFWwindow*)App::Get()->GetWindow()->GetHandle();

	bool Input::IsKeyDown(KeyCode key_code)
	{
		AP_PROFILE_FN();
		return glfwGetKey((GLFWwindow*)App::Get()->GetWindow()->GetHandle(), KeyCodeToGLFWKeyCode(key_code)) == (GLFW_PRESS || GLFW_REPEAT);
	}

	bool Input::WasKeyDown(KeyCode key_code)
	{
		AP_PROFILE_FN();
		AP_ERROR_C("WasKeyDown is not supported in OpenGL");
		return false;
	}

	bool Input::IsMouseButtonDown(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		return glfwGetKey((GLFWwindow*)App::Get()->GetWindow()->GetHandle(), MouseCodeToGLFWMouseButton(mouse_code)) == GLFW_PRESS;
	}

	bool Input::WasMouseButtonDown(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		AP_ERROR_C("WasMouseButtonDown is not supported in OpenGL");
		return false;
	}

	std::array<int, 2> Input::GetMousePos()
	{
		AP_PROFILE_FN();
		double x, y;
		glfwGetCursorPos((GLFWwindow*)App::Get()->GetWindow()->GetHandle(), &x, &y);
		return std::array<int, 2>({ (int)x, (int)y });
	}

	int Input::GetMouseX()
	{
		AP_PROFILE_FN();
		return GetMousePos()[0];
	}

	int Input::GetMouseY()
	{
		AP_PROFILE_FN();
		return GetMousePos()[1];
	}

}