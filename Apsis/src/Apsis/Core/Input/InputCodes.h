#pragma once
#include <iostream>

namespace A {

	typedef enum class MouseCode : unsigned short
	{
		Unknown = 0,
		Left,
		Right,
		Middle,
		X1,
		X2
	} Mouse;

	const char* MouseCodeToString(MouseCode mouse_code);
	std::ostream& operator<<(std::ostream& os, const MouseCode& mouse_code);

	// ASCII
	typedef enum class KeyCode : unsigned short
	{
		Unknown				= 0,
		
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

	const char* KeyCodeToString(KeyCode key_code);
	std::ostream& operator<<(std::ostream& os, const KeyCode& key_code);

}