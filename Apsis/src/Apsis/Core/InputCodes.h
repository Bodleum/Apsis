#pragma once

namespace A {

	typedef enum class MouseCode : unsigned short
	{
		Unknown = -1,
		Left = 0,
		Right,
		Middle,
		X1,
		X2
	} Mouse;

	inline std::string MouseCodeToString(MouseCode mouse_code)
	{
		switch (mouse_code)
		{
		case A::MouseCode::Unknown:	return "Unknown";
		case A::MouseCode::Left:	return "Left";
		case A::MouseCode::Right:	return "Right";
		case A::MouseCode::Middle:	return "Middle";
		case A::MouseCode::X1:		return "X1";
		case A::MouseCode::X2:		return "X2";
		default:					return "Unknown";
		}
	}

	// Printing
	inline std::ostream& operator<<(std::ostream& os, const MouseCode& mouse_code)
	{
		return os << (unsigned short)mouse_code;
	}

	typedef enum class KeyCode : unsigned short
	{
		Unknown = -1,
		None = 0,

		// Alphabet
		A = 1,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		// Numbers
		Num0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,

		Escape,
		LControl,
		LShift,
		LAlt,
		LSystem,
		RControl,
		RShift,
		RAlt,
		RSystem,
		Menu,

		LBracket,
		RBracket,
		Semicolon,
		Comma,
		Period,
		Quote,
		Slash,
		Backslash,
		Tilde,
		Equal,
		Hyphen,

		Space,
		Enter,
		Backspace,
		Tab,
		PageUp,
		PageDown,
		End,
		Home,
		Insert,
		Delete,

		Add,
		Subtract,
		Multiply,
		Divide,

		Left,
		Right,
		Up,
		Down,

		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,

		Pause
	} Key;

}