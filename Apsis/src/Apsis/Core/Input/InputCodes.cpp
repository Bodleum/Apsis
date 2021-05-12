#include "apch.h"
#include "InputCodes.h"

namespace A {

	const char* MouseCodeToString(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		static std::unordered_map<MouseCode, const char*> stringMap =
		{
			{ MouseCode::Left, "Left" },
			{ MouseCode::Right,  "Right" },
			{ MouseCode::Middle,  "Middle" },
			{ MouseCode::X1,  "X1" },
			{ MouseCode::X2,  "X2" }
		};

		try
		{
			return stringMap.at(mouse_code);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("MouseCode {0} not supported", (unsigned short)mouse_code);
			return "Unknown";
		}
	}

	// Printing
	std::ostream& operator<<(std::ostream& os, const MouseCode& mouse_code)
	{
		return os << MouseCodeToString(mouse_code);
	}


	const char* KeyCodeToString(KeyCode key_code)
	{
		static std::unordered_map<KeyCode, const char*> stringMap =
		{
			{ KeyCode::Space,				"Space" },
			{ KeyCode::ExclamationMark,		"ExclamationMark" },
			{ KeyCode::DoubleQuotes,		"DoubleQuotes" },
			{ KeyCode::NumberSign,			"NumberSign" },
			{ KeyCode::Dollar,				"Dollar" },
			{ KeyCode::Percent,				"Percent" },
			{ KeyCode::Ampersand,			"Ampersand" },
			{ KeyCode::SingleQuote,			"SingleQuote" },
			{ KeyCode::OpenBracket,			"OpenBracket" },
			{ KeyCode::CloseBracket,		"CloseBracket" },
			{ KeyCode::Asterisk,			"Asterisk" },
			{ KeyCode::Plus,				"Plus" },
			{ KeyCode::Comma,				"Comma" },
			{ KeyCode::Hyphen,				"Hyphen" },
			{ KeyCode::Dot,					"Dot" },
			{ KeyCode::Slash,				"Slash" },

			// Numbers
			{ KeyCode::Num0,				"Num0" },
			{ KeyCode::Num1,				"Num1" },
			{ KeyCode::Num2,				"Num2" },
			{ KeyCode::Num3,				"Num3" },
			{ KeyCode::Num4,				"Num4" },
			{ KeyCode::Num5,				"Num5" },
			{ KeyCode::Num6,				"Num6" },
			{ KeyCode::Num7,				"Num7" },
			{ KeyCode::Num8,				"Num8" },
			{ KeyCode::Num9,				"Num9" },

			{ KeyCode::Colon,				"Colon" },
			{ KeyCode::Semicolon,			"Semicolon" },
			{ KeyCode::LessThan,			"LessThan" },
			{ KeyCode::Equal,				"Equal" },
			{ KeyCode::GreaterThan,			"GreaterThan" },
			{ KeyCode::QuestionMark,		"QuestionMark" },
			{ KeyCode::At,					"At" },

			// Alphabet
			{ KeyCode::A,					"A" },
			{ KeyCode::B,					"B" },
			{ KeyCode::C,					"C" },
			{ KeyCode::D,					"D" },
			{ KeyCode::E,					"E" },
			{ KeyCode::F,					"F" },
			{ KeyCode::G,					"G" },
			{ KeyCode::H,					"H" },
			{ KeyCode::I,					"I" },
			{ KeyCode::J,					"J" },
			{ KeyCode::K,					"K" },
			{ KeyCode::L,					"L" },
			{ KeyCode::M,					"M" },
			{ KeyCode::N,					"N" },
			{ KeyCode::O,					"O" },
			{ KeyCode::P,					"P" },
			{ KeyCode::Q,					"Q" },
			{ KeyCode::R,					"R" },
			{ KeyCode::S,					"S" },
			{ KeyCode::T,					"T" },
			{ KeyCode::U,					"U" },
			{ KeyCode::V,					"V" },
			{ KeyCode::W,					"W" },
			{ KeyCode::X,					"X" },
			{ KeyCode::Y,					"Y" },
			{ KeyCode::Z,					"Z" },

			{ KeyCode::OpenSquareBracket,	"OpenSquareBracket" },
			{ KeyCode::Backslash,			"Backslash" },
			{ KeyCode::CloseSquareBracket,	"CloseSquareBracket" },
			{ KeyCode::Caret,				"Caret" },
			{ KeyCode::Underscore,			"Underscore" },
			{ KeyCode::Grave,				"Grave" },


			{ KeyCode::OpenCurlyBracket,	"OpenCurlyBracket" },
			{ KeyCode::Bar,					"Bar" },
			{ KeyCode::CloseCurlyBracket,	"CloseCurlyBracket" },
			{ KeyCode::Tilde,				"Tilde" },

			{ KeyCode::Europe1,				"Europe1" },
			{ KeyCode::Europe2,				"Europe2" },
			
			/*
			* Extended ASCII
			*/
			
			// Function keys
			{ KeyCode::Escape,				"Escape" },
			{ KeyCode::Enter,				"Enter" },
			{ KeyCode::Tab,					"Tab" },
			{ KeyCode::Backspace,			"Backspace" },
			{ KeyCode::Insert,				"Insert" },
			{ KeyCode::Delete,				"Delete" },
			{ KeyCode::Right,				"Right" },
			{ KeyCode::Left,				"Left" },
			{ KeyCode::Down,				"Down" },
			{ KeyCode::Up,					"Up" },
			{ KeyCode::PageUp,				"PageUp" },
			{ KeyCode::PageDown,			"PageDown" },
			{ KeyCode::Home,				"Home" },
			{ KeyCode::End,					"End" },
			{ KeyCode::CapsLock,			"CapsLock" },
			{ KeyCode::ScrollLock,			"ScrollLock" },
			{ KeyCode::NumLock,				"NumLock" },
			{ KeyCode::PrintScreen,			"PrintScreen" },
			{ KeyCode::Pause,				"Pause" },
			{ KeyCode::Break,				"Break" },

			{ KeyCode::F1,					"F1" },
			{ KeyCode::F2,					"F2" },
			{ KeyCode::F3,					"F3" },
			{ KeyCode::F4,					"F4" },
			{ KeyCode::F5,					"F5" },
			{ KeyCode::F6,					"F6" },
			{ KeyCode::F7,					"F7" },
			{ KeyCode::F8,					"F8" },
			{ KeyCode::F9,					"F9" },
			{ KeyCode::F10,					"F10" },
			{ KeyCode::F11,					"F11" },
			{ KeyCode::F12,					"F12" },
			{ KeyCode::F13,					"F13" },
			{ KeyCode::F14,					"F14" },
			{ KeyCode::F15,					"F15" },
			{ KeyCode::F16,					"F16" },
			{ KeyCode::F17,					"F17" },
			{ KeyCode::F18,					"F18" },
			{ KeyCode::F19,					"F19" },
			{ KeyCode::F20,					"F20" },
			{ KeyCode::F21,					"F21" },
			{ KeyCode::F22,					"F22" },
			{ KeyCode::F23,					"F23" },
			{ KeyCode::F24,					"F24" },
			{ KeyCode::F25,					"F25" },

			// Keypad
			{ KeyCode::Numpad0,				"Numpad0" },
			{ KeyCode::Numpad1,				"Numpad1" },
			{ KeyCode::Numpad2,				"Numpad2" },
			{ KeyCode::Numpad3,				"Numpad3" },
			{ KeyCode::Numpad4,				"Numpad4" },
			{ KeyCode::Numpad5,				"Numpad5" },
			{ KeyCode::Numpad6,				"Numpad6" },
			{ KeyCode::Numpad7,				"Numpad7" },
			{ KeyCode::Numpad8,				"Numpad8" },
			{ KeyCode::Numpad9,				"Numpad9" },
			{ KeyCode::NumpadDecimal,		"NumpadDecimal" },
			{ KeyCode::NumpadDivide,		"NumpadDivide" },
			{ KeyCode::NumpadMultiply,		"NumpadMultiply" },
			{ KeyCode::NumpadSubtract,		"NumpadSubtract" },
			{ KeyCode::NumpadPlus,			"NumpadPlus" },
			{ KeyCode::NumpadEnter,			"NumpadEnter" },
			{ KeyCode::NumpadEqual,			"NumpadEqual" },

			// Modifiers
			{ KeyCode::LeftShift,			"LeftShift" },
			{ KeyCode::LeftControl,			"LeftControl" },
			{ KeyCode::LeftAlt,				"LeftAlt" },
			{ KeyCode::LeftSuper,			"LeftSuper" },
			{ KeyCode::RightShift,			"RightShift" },
			{ KeyCode::RightControl,		"RightControl" },
			{ KeyCode::RightAlt,			"RightAlt" },
			{ KeyCode::RightSuper,			"RightSuper" },

			{ KeyCode::Menu,				"Menu" }
		};
		
		try
		{
			return stringMap.at(key_code);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("KeyCode {0} not supported", (unsigned short)key_code);
			return "Unknown";
		}
	}

	// Printing
	std::ostream& operator<<(std::ostream& os, const KeyCode& key_code)
	{
		return os << KeyCodeToString(key_code);
	}
}