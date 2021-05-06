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
		AP_PROFILE_FN();

		switch (mouse_code)
		{
			case MouseCode::Unknown:	return "Unknown";
			case MouseCode::Left:		return "Left";
			case MouseCode::Right:		return "Right";
			case MouseCode::Middle:		return "Middle";
			case MouseCode::X1:			return "X1";
			case MouseCode::X2:			return "X2";
			default:					return "Unknown";
		}
	}

	// Printing
	inline std::ostream& operator<<(std::ostream& os, const MouseCode& mouse_code)
	{
		AP_PROFILE_FN();
		return os << (unsigned short)mouse_code;
	}

	// ASCII
	typedef enum class KeyCode : unsigned short
	{
		Unknown				= -1,
		Null				= 0,

		
		Space				= 32,
		ExclamationMark		= 33,
		DoubleQuotes		= 34,
		NumberSign			= 35,
		Dollar				= 36,
		Percent				= 37,
		Ampersand			= 38,
		SingleQuote			= 39,
		OpenBracket			= 40,
		CloseBracket		= 41,
		Asterisk			= 42,
		Plus				= 43,
		Comma				= 44,
		Hyphen				= 45,
		Dot					= 46,
		Slash				= 47,

		// Numbers
		Num0				= 48,
		Num1				= 49,
		Num2				= 50,
		Num3				= 51,
		Num4				= 52,
		Num5				= 53,
		Num6				= 54,
		Num7				= 55,
		Num8				= 56,
		Num9				= 57,

		Colon				= 58,
		Semicolon			= 59,
		LessThan			= 60,
		Equal				= 61,
		GreaterThan			= 62,
		QuestionMark		= 63,
		At					= 64,

		// Alphabet
		A					= 65,
		B					= 66,
		C					= 67,
		D					= 68,
		E					= 69,
		F					= 70,
		G					= 71,
		H					= 72,
		I					= 73,
		J					= 74,
		K					= 75,
		L					= 76,
		M					= 77,
		N					= 78,
		O					= 79,
		P					= 80,
		Q					= 81,
		R					= 82,
		S					= 83,
		T					= 84,
		U					= 85,
		V					= 86,
		W					= 87,
		X					= 88,
		Y					= 89,
		Z					= 90,

		OpenSquareBracket	= 91,
		Backslash			= 92,
		CloseSquareBracket	= 93,
		Caret				= 94,
		Underscore			= 95,
		Grave				= 96,


		OpenCurlyBracket	= 123,
		Bar					= 124,
		CloseCurlyBracket	= 125,
		Tilde				= 126,

		Europe1				= 127,
		Europe2				= 128,

		/*
		* Extended ASCII
		*/

		// Function keys
		Escape				= 256,
		Enter				= 257,
		Tab					= 258,
		Backspace			= 259,
		Insert				= 260,
		Delete				= 261,
		Right				= 262,
		Left				= 263,
		Down				= 264,
		Up					= 265,
		PageUp				= 266,
		PageDown			= 267,
		Home				= 268,
		End					= 269,
		CapsLock			= 280,
		ScrollLock			= 281,
		NumLock				= 282,
		PrintScreen			= 283,
		Pause				= 284,
		Break				= 285,

		F1					= 290,
		F2					= 291,
		F3					= 292,
		F4					= 293,
		F5					= 294,
		F6					= 295,
		F7					= 296,
		F8					= 297,
		F9					= 298,
		F10					= 299,
		F11					= 300,
		F12					= 301,
		F13					= 302,
		F14					= 303,
		F15					= 304,
		F16					= 305,
		F17					= 306,
		F18					= 307,
		F19					= 308,
		F20					= 309,
		F21					= 310,
		F22					= 311,
		F23					= 312,
		F24					= 313,
		F25					= 314,

		// Keypad
		Numpad0				= 320,
		Numpad1				= 321,
		Numpad2				= 322,
		Numpad3				= 323,
		Numpad4				= 324,
		Numpad5				= 325,
		Numpad6				= 326,
		Numpad7				= 327,
		Numpad8				= 328,
		Numpad9				= 329,
		NumpadDecimal		= 330,
		NumpadDivide		= 331,
		NumpadMultiply		= 332,
		NumpadSubtract		= 333,
		NumpadPlus			= 334,
		NumpadEnter			= 335,
		NumpadEqual			= 336,

		// Modifiers
		LeftShift			= 340,
		LeftControl			= 341,
		LeftAlt				= 342,
		LeftSuper			= 343,
		RightShift			= 344,
		RightControl		= 345,
		RightAlt			= 346,
		RightSuper			= 347,

		Menu				= 348,
	} Key;

	inline std::string KeyCodeToString(KeyCode key_code)
	{
		AP_PROFILE_FN();

		switch (key_code)
		{
			case KeyCode::Null:					return "Null";

			case KeyCode::Space:				return "Space";
			case KeyCode::ExclamationMark:		return "ExclamationMark";
			case KeyCode::DoubleQuotes:			return "DoubleQuotes";
			case KeyCode::NumberSign:			return "NumberSign";
			case KeyCode::Dollar:				return "Dollar";
			case KeyCode::Percent:				return "Percent";
			case KeyCode::Ampersand:			return "Ampersand";
			case KeyCode::SingleQuote:			return "SingleQuote";
			case KeyCode::OpenBracket:			return "OpenBracket";
			case KeyCode::CloseBracket:			return "CloseBracket";
			case KeyCode::Asterisk:				return "Asterisk";
			case KeyCode::Plus:					return "Plus";
			case KeyCode::Comma:				return "Comma";
			case KeyCode::Hyphen:				return "Hyphen";
			case KeyCode::Dot:					return "Dot";
			case KeyCode::Slash:				return "Slash";

			// Numbers
			case KeyCode::Num0:					return "Num0";
			case KeyCode::Num1:					return "Num1";
			case KeyCode::Num2:					return "Num2";
			case KeyCode::Num3:					return "Num3";
			case KeyCode::Num4:					return "Num4";
			case KeyCode::Num5:					return "Num5";
			case KeyCode::Num6:					return "Num6";
			case KeyCode::Num7:					return "Num7";
			case KeyCode::Num8:					return "Num8";
			case KeyCode::Num9:					return "Num9";

			case KeyCode::Colon:				return "Colon";
			case KeyCode::Semicolon:			return "Semicolon";
			case KeyCode::LessThan:				return "LessThan";
			case KeyCode::Equal:				return "Equal";
			case KeyCode::GreaterThan:			return "GreaterThan";
			case KeyCode::QuestionMark:			return "QuestionMark";
			case KeyCode::At:					return "At";

			// Alphabet
			case KeyCode::A:					return "A";
			case KeyCode::B:					return "B";
			case KeyCode::C:					return "C";
			case KeyCode::D:					return "D";
			case KeyCode::E:					return "E";
			case KeyCode::F:					return "F";
			case KeyCode::G:					return "G";
			case KeyCode::H:					return "H";
			case KeyCode::I:					return "I";
			case KeyCode::J:					return "J";
			case KeyCode::K:					return "K";
			case KeyCode::L:					return "L";
			case KeyCode::M:					return "M";
			case KeyCode::N:					return "N";
			case KeyCode::O:					return "O";
			case KeyCode::P:					return "P";
			case KeyCode::Q:					return "Q";
			case KeyCode::R:					return "R";
			case KeyCode::S:					return "S";
			case KeyCode::T:					return "T";
			case KeyCode::U:					return "U";
			case KeyCode::V:					return "V";
			case KeyCode::W:					return "W";
			case KeyCode::X:					return "X";
			case KeyCode::Y:					return "Y";
			case KeyCode::Z:					return "Z";

			case KeyCode::OpenSquareBracket:	return "OpenSquareBracket";
			case KeyCode::Backslash:			return "Backslash";
			case KeyCode::CloseSquareBracket:	return "CloseSquareBracket";
			case KeyCode::Caret:				return "Caret";
			case KeyCode::Underscore:			return "Underscore";
			case KeyCode::Grave:				return "Grave";


			case KeyCode::OpenCurlyBracket:		return "OpenCurlyBracket";
			case KeyCode::Bar:					return "Bar";
			case KeyCode::CloseCurlyBracket:	return "CloseCurlyBracket";
			case KeyCode::Tilde:				return "Tilde";

			case KeyCode::Europe1:				return "Europe1";
			case KeyCode::Europe2:				return "Europe2";
			
			/*
			* Extended ASCII
			*/
			
			// Function keys
			case KeyCode::Escape:				return "Escape";
			case KeyCode::Enter:				return "Enter";
			case KeyCode::Tab:					return "Tab";
			case KeyCode::Backspace:			return "Backspace";
			case KeyCode::Insert:				return "Insert";
			case KeyCode::Delete:				return "Delete";
			case KeyCode::Right:				return "Right";
			case KeyCode::Left:					return "Left";
			case KeyCode::Down:					return "Down";
			case KeyCode::Up:					return "Up";
			case KeyCode::PageUp:				return "PageUp";
			case KeyCode::PageDown:				return "PageDown";
			case KeyCode::Home:					return "Home";
			case KeyCode::End:					return "End";
			case KeyCode::CapsLock:				return "CapsLock";
			case KeyCode::ScrollLock:			return "ScrollLock";
			case KeyCode::NumLock:				return "NumLock";
			case KeyCode::PrintScreen:			return "PrintScreen";
			case KeyCode::Pause:				return "Pause";
			case KeyCode::Break:				return "Break";

			case KeyCode::F1:					return "F1";
			case KeyCode::F2:					return "F2";
			case KeyCode::F3:					return "F3";
			case KeyCode::F4:					return "F4";
			case KeyCode::F5:					return "F5";
			case KeyCode::F6:					return "F6";
			case KeyCode::F7:					return "F7";
			case KeyCode::F8:					return "F8";
			case KeyCode::F9:					return "F9";
			case KeyCode::F10:					return "F10";
			case KeyCode::F11:					return "F11";
			case KeyCode::F12:					return "F12";
			case KeyCode::F13:					return "F13";
			case KeyCode::F14:					return "F14";
			case KeyCode::F15:					return "F15";
			case KeyCode::F16:					return "F16";
			case KeyCode::F17:					return "F17";
			case KeyCode::F18:					return "F18";
			case KeyCode::F19:					return "F19";
			case KeyCode::F20:					return "F20";
			case KeyCode::F21:					return "F21";
			case KeyCode::F22:					return "F22";
			case KeyCode::F23:					return "F23";
			case KeyCode::F24:					return "F24";
			case KeyCode::F25:					return "F25";

			// Keypad
			case KeyCode::Numpad0:				return "Numpad0";
			case KeyCode::Numpad1:				return "Numpad1";
			case KeyCode::Numpad2:				return "Numpad2";
			case KeyCode::Numpad3:				return "Numpad3";
			case KeyCode::Numpad4:				return "Numpad4";
			case KeyCode::Numpad5:				return "Numpad5";
			case KeyCode::Numpad6:				return "Numpad6";
			case KeyCode::Numpad7:				return "Numpad7";
			case KeyCode::Numpad8:				return "Numpad8";
			case KeyCode::Numpad9:				return "Numpad9";
			case KeyCode::NumpadDecimal:		return "NumpadDecimal";
			case KeyCode::NumpadDivide:			return "NumpadDivide";
			case KeyCode::NumpadMultiply:		return "NumpadMultiply";
			case KeyCode::NumpadSubtract:		return "NumpadSubtract";
			case KeyCode::NumpadPlus:			return "NumpadPlus";
			case KeyCode::NumpadEnter:			return "NumpadEnter";
			case KeyCode::NumpadEqual:			return "NumpadEqual";

			// Modifiers
			case KeyCode::LeftShift:			return "LeftShift";
			case KeyCode::LeftControl:			return "LeftControl";
			case KeyCode::LeftAlt:				return "LeftAlt";
			case KeyCode::LeftSuper:			return "LeftSuper";
			case KeyCode::RightShift:			return "RightShift";
			case KeyCode::RightControl:			return "RightControl";
			case KeyCode::RightAlt:				return "RightAlt";
			case KeyCode::RightSuper:			return "RightSuper";

			case KeyCode::Menu:					return "Menu";
			default:							return "Unknown";
		}
	}

	// Printing
	inline std::ostream& operator<<(std::ostream& os, const KeyCode& key_code)
	{
		AP_PROFILE_FN();
		return os << (unsigned short)key_code;
	}
	
}