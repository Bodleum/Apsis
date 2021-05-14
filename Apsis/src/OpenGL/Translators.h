#pragma once
#include "Apsis/Core/Input/InputCodes.h"
	//#include <iostream>

namespace A {

	MouseCode GLFWMouseButtonToMouseCode(int mouse_button);
	int MouseCodeToGLFWMouseButton(MouseCode mouse_code);
	
	KeyCode GLFWKeyCodeToKeyCode(int key_code);
	int KeyCodeToGLFWKeyCode(KeyCode key_code);


}