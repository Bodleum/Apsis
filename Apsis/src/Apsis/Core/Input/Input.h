#pragma once
#include "Apsis/Core/Input/InputCodes.h"

namespace A {

	struct Input
	{
		static bool IsKeyDown(KeyCode key_code);
		static bool WasKeyDown(KeyCode key_code);
		static bool IsMouseButtonDown(MouseCode mouse_code);
		static bool WasMouseButtonDown(MouseCode mouse_code);
		static std::array<int, 2> GetMousePos();
		static int GetMouseX();
		static int GetMouseY();
	};

}