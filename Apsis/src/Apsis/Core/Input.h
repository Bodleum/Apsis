#pragma once
#include "apch.h"		// Shared
#include "InputCodes.h"

namespace A {

	class Input
	{
	public:
		static Shared<Input> Create();

		virtual bool IsKeyDown(KeyCode key_code) = 0;
		virtual bool WasKeyDown(KeyCode key_code) = 0;
		virtual bool IsMouseButtonDown(MouseCode mouse_code) = 0;
		virtual bool WasMouseButtonDown(MouseCode mouse_code) = 0;
		virtual std::array<int, 2> GetMousePos() = 0;
		virtual int GetMouseX() = 0;
		virtual int GetMouseY() = 0;

		Input(Input const&) = delete;
		Input& operator=(Input const&) = delete;

	protected:
		Input() {};

	private:
		static Shared<Input> s_Instance;
	};

}