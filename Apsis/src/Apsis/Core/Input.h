#pragma once
#include "apch.h"		// Shared
#include "InputCodes.h"

namespace A {

	class Input
	{
	public:
		static Unique<Input>& Create();

		static inline bool IsKeyDown(KeyCode key_code) { return s_Instance->IsKeyDownImpl(key_code); }
		static inline bool WasKeyDown(KeyCode key_code) { return s_Instance->WasKeyDownImpl(key_code); }
		static inline bool IsMouseButtonDown(MouseCode mouse_code) { return s_Instance->IsMouseButtonDownImpl(mouse_code); }
		static inline bool WasMouseButtonDown(MouseCode mouse_code) { return s_Instance->WasMouseButtonDownImpl(mouse_code); }
		static inline std::array<int, 2> GetMousePos() { return s_Instance->GetMousePosImpl(); }
		static inline int GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static inline int GetMouseY() { return s_Instance->GetMouseYImpl(); }

		Input(Input const&) = delete;
		Input& operator=(Input const&) = delete;

	protected:
		Input() = default;

		virtual bool IsKeyDownImpl(KeyCode key_code) = 0;
		virtual bool WasKeyDownImpl(KeyCode key_code) = 0;
		virtual bool IsMouseButtonDownImpl(MouseCode mouse_code) = 0;
		virtual bool WasMouseButtonDownImpl(MouseCode mouse_code) = 0;
		virtual std::array<int, 2> GetMousePosImpl() = 0;
		virtual int GetMouseXImpl() = 0;
		virtual int GetMouseYImpl() = 0;

	private:
		static Unique<Input> s_Instance;
	};

}