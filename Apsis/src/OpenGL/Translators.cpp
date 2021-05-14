#include "apch.h"
#include "Translators.h"
	//#include "Apsis/Core/Input/InputCodes.h"
	//	#include <iostream>

namespace A {

	MouseCode GLFWMouseButtonToMouseCode(int mouse_button)
	{
		static std::unordered_map<int, MouseCode> buttonMap =
		{
			{0, Mouse::Left},
			{1, Mouse::Right},
			{2, Mouse::Middle},
			{3, Mouse::X1},
			{4, Mouse::X2}
		};

		try
		{
			return buttonMap.at(mouse_button);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("Unknown mouse button {0}", mouse_button);
			return Mouse::Unknown;
		}
	}

	int MouseCodeToGLFWMouseButton(MouseCode mouse_code)
	{
		static std::unordered_map<MouseCode, int> mouseCodeMap =
		{
			{Mouse::Left, 0},
			{Mouse::Right, 1},
			{Mouse::Middle, 2},
			{Mouse::X1, 3},
			{Mouse::X2, 4}
		};

		try
		{
			return mouseCodeMap.at(mouse_code);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("Unknown mouse code {0}", (unsigned short)mouse_code);
			return -1;
		}
	}

	KeyCode GLFWKeyCodeToKeyCode(int key_code)
	{

		static std::unordered_map<int, KeyCode> keyCodeMap =
		{
			{44, Key::Comma},
			{96, Key::Grave},
			{32, Key::Space},
			{48, Key::Num0},
			{39, Key::SingleQuote},
			{47, Key::Slash},
			{45, Key::Hyphen},
			{46, Key::Dot},
			{49, Key::Num1},
			{50, Key::Num2},
			{51, Key::Num3},
			{52, Key::Num4},
			{53, Key::Num5},
			{54, Key::Num6},
			{55, Key::Num7},
			{56, Key::Num8},
			{263, Key::Left},
			{57, Key::Num9},
			{59, Key::Semicolon},
			{61, Key::Equal},
			{65, Key::A},
			{66, Key::B},
			{265, Key::Up},
			{67, Key::C},
			{260, Key::Insert},
			{68, Key::D},
			{259, Key::Backspace},
			{69, Key::E},
			{70, Key::F},
			{71, Key::G},
			{72, Key::H},
			{73, Key::I},
			{258, Key::Tab},
			{74, Key::J},
			{75, Key::K},
			{268, Key::Home},
			{76, Key::L},
			{267, Key::PageDown},
			{77, Key::M},
			{262, Key::Right},
			{78, Key::N},
			{79, Key::O},
			{256, Key::Escape},
			{80, Key::P},
			{81, Key::Q},
			{266, Key::PageUp},
			{82, Key::R},
			{83, Key::S},
			{84, Key::T},
			{85, Key::U},
			{86, Key::V},
			{87, Key::W},
			{264, Key::Down},
			{88, Key::X},
			{89, Key::Y},
			{90, Key::Z},
			{91, Key::OpenSquareBracket},
			{92, Key::Backslash},
			{93, Key::CloseSquareBracket},
			{161, Key::Europe1},
			{162, Key::Europe2},
			{257, Key::Enter},
			{261, Key::Delete},
			{269, Key::End},
			{280, Key::CapsLock},
			{281, Key::ScrollLock},
			{282, Key::NumLock},
			{283, Key::PrintScreen},
			{284, Key::Pause},
			{290, Key::F1},
			{291, Key::F2},
			{292, Key::F3},
			{293, Key::F4},
			{294, Key::F5},
			{295, Key::F6},
			{296, Key::F7},
			{297, Key::F8},
			{298, Key::F9},
			{299, Key::F10},
			{300, Key::F11},
			{301, Key::F12},
			{302, Key::F13},
			{303, Key::F14},
			{304, Key::F15},
			{305, Key::F16},
			{306, Key::F17},
			{307, Key::F18},
			{308, Key::F19},
			{309, Key::F20},
			{310, Key::F21},
			{311, Key::F22},
			{312, Key::F23},
			{313, Key::F24},
			{314, Key::F25},
			{320, Key::Numpad0},
			{321, Key::Numpad1},
			{322, Key::Numpad2},
			{323, Key::Numpad3},
			{324, Key::Numpad4},
			{325, Key::Numpad5},
			{326, Key::Numpad6},
			{327, Key::Numpad7},
			{328, Key::Numpad8},
			{329, Key::Numpad9},
			{330, Key::NumpadDecimal},
			{331, Key::NumpadDivide},
			{332, Key::NumpadMultiply},
			{333, Key::NumpadSubtract},
			{334, Key::NumpadPlus},
			{335, Key::NumpadEnter},
			{336, Key::NumpadEqual},
			{340, Key::LeftShift},
			{341, Key::LeftControl},
			{342, Key::LeftAlt},
			{343, Key::LeftSuper},
			{344, Key::RightShift},
			{345, Key::RightControl},
			{346, Key::RightAlt},
			{347, Key::RightSuper},
			{348, Key::Menu}
		};

		try
		{
			return keyCodeMap.at(key_code);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("Unknown key code {0}", key_code);
			return Key::Unknown;
		}
	}

	int KeyCodeToGLFWKeyCode(KeyCode key_code)
	{
		static std::unordered_map<KeyCode, int> keyCodeMap =
		{
			{Key::Unknown, -1},
			{Key::Comma, 44},
			{Key::Grave, 96},
			{Key::Space, 32},
			{Key::Num0, 48},
			{Key::SingleQuote, 39},
			{Key::Slash, 47},
			{Key::Hyphen, 45},
			{Key::Dot, 46},
			{Key::Num1, 49},
			{Key::Num2, 50},
			{Key::Num3, 51},
			{Key::Num4, 52},
			{Key::Num5, 53},
			{Key::Num6, 54},
			{Key::Num7, 55},
			{Key::Num8, 56},
			{Key::Left, 263},
			{Key::Num9, 57},
			{Key::Semicolon, 59},
			{Key::Equal, 61},
			{Key::A, 65},
			{Key::B, 66},
			{Key::Up, 265},
			{Key::C, 67},
			{Key::Insert, 260},
			{Key::D, 68},
			{Key::Backspace, 259},
			{Key::E, 69},
			{Key::F, 70},
			{Key::G, 71},
			{Key::H, 72},
			{Key::I, 73},
			{Key::Tab, 258},
			{Key::J, 74},
			{Key::K, 75},
			{Key::Home, 268},
			{Key::L, 76},
			{Key::PageDown, 267},
			{Key::M, 77},
			{Key::Right, 262},
			{Key::N, 78},
			{Key::O, 79},
			{Key::Escape, 256},
			{Key::P, 80},
			{Key::Q, 81},
			{Key::PageUp, 266},
			{Key::R, 82},
			{Key::S, 83},
			{Key::T, 84},
			{Key::U, 85},
			{Key::V, 86},
			{Key::W, 87},
			{Key::Down, 264},
			{Key::X, 88},
			{Key::Y, 89},
			{Key::Z, 90},
			{Key::OpenSquareBracket, 91},
			{Key::Backslash, 92},
			{Key::CloseSquareBracket, 93},
			{Key::Europe1, 161},
			{Key::Europe2, 162},
			{Key::Enter, 257},
			{Key::Delete, 261},
			{Key::End, 269},
			{Key::CapsLock, 280},
			{Key::ScrollLock, 281},
			{Key::NumLock, 282},
			{Key::PrintScreen, 283},
			{Key::Pause, 284},
			{Key::F1, 290},
			{Key::F2, 291},
			{Key::F3, 292},
			{Key::F4, 293},
			{Key::F5, 294},
			{Key::F6, 295},
			{Key::F7, 296},
			{Key::F8, 297},
			{Key::F9, 298},
			{Key::F10, 299},
			{Key::F11, 300},
			{Key::F12, 301},
			{Key::F13, 302},
			{Key::F14, 303},
			{Key::F15, 304},
			{Key::F16, 305},
			{Key::F17, 306},
			{Key::F18, 307},
			{Key::F19, 308},
			{Key::F20, 309},
			{Key::F21, 310},
			{Key::F22, 311},
			{Key::F23, 312},
			{Key::F24, 313},
			{Key::F25, 314},
			{Key::Numpad0, 320},
			{Key::Numpad1, 321},
			{Key::Numpad2, 322},
			{Key::Numpad3, 323},
			{Key::Numpad4, 324},
			{Key::Numpad5, 325},
			{Key::Numpad6, 326},
			{Key::Numpad7, 327},
			{Key::Numpad8, 328},
			{Key::Numpad9, 329},
			{Key::NumpadDecimal, 330},
			{Key::NumpadDivide, 331},
			{Key::NumpadMultiply, 332},
			{Key::NumpadSubtract, 333},
			{Key::NumpadPlus, 334},
			{Key::NumpadEnter, 335},
			{Key::NumpadEqual, 336},
			{Key::LeftShift, 340},
			{Key::LeftControl, 341},
			{Key::LeftAlt, 342},
			{Key::LeftSuper, 343},
			{Key::RightShift, 344},
			{Key::RightControl, 345},
			{Key::RightAlt, 346},
			{Key::RightSuper, 347},
			{Key::Menu, 348}
		};

		try
		{
			return keyCodeMap.at(key_code);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("Unknown key code {0}", key_code);
			return -1;
		}
	}

}