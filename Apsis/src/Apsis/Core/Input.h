#pragma once
#include "apch.h"		// Shared
#include "InputCodes.h"

namespace A {

	class Input
	{
	public:
		static Shared<Input> Create();

		static bool IsKeyDown(KeyCode key_code) { s_Instance->IsKeyDownImpl(key_code); }
		static bool WasKeyDown(KeyCode key_code) { s_Instance->WasKeyDownImpl(key_code); }
		static bool IsMouseButtonDown(MouseCode mouse_code) { s_Instance->IsMouseButtonDownImpl(mouse_code); }
		static bool WasMouseButtonDown(MouseCode mouse_code) { s_Instance->WasMouseButtonDownImpl(mouse_code); }
		static std::array<int, 2> GetMousePos() { s_Instance->GetMousePosImpl(); }
		static int GetMouseX() { s_Instance->GetMouseXImpl(); }
		static int GetMouseY() { s_Instance->GetMouseYImpl(); }

		Input(Input const&) = delete;
		Input& operator=(Input const&) = delete;

	protected:
		Input() {};

		virtual bool IsKeyDownImpl(KeyCode key_code) = 0;
		virtual bool WasKeyDownImpl(KeyCode key_code) = 0;
		virtual bool IsMouseButtonDownImpl(MouseCode mouse_code) = 0;
		virtual bool WasMouseButtonDownImpl(MouseCode mouse_code) = 0;
		virtual std::array<int, 2> GetMousePosImpl() = 0;
		virtual int GetMouseXImpl() = 0;
		virtual int GetMouseYImpl() = 0;

	private:
		static Shared<Input> s_Instance;
	};

}