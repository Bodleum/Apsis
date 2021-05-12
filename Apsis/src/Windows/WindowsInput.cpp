#include "apch.h"
#include "Apsis/Core/Input/Input.h"

namespace A {

	int KeyCodeToVirtualKeyCode(KeyCode key_code);
	int MouseCodeToVirtualKeyCode(MouseCode mouse_code);

	bool Input::IsKeyDown(KeyCode key_code)
	{
		AP_PROFILE_FN();
		return 0x80000000 & GetAsyncKeyState(KeyCodeToVirtualKeyCode(key_code));
	}

	bool Input::WasKeyDown(KeyCode key_code)
	{
		AP_PROFILE_FN();
		return 0x00000001 & GetAsyncKeyState(KeyCodeToVirtualKeyCode(key_code));
	}

	bool Input::IsMouseButtonDown(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		return 0x80000000 & GetAsyncKeyState(MouseCodeToVirtualKeyCode(mouse_code));
	}

	bool Input::WasMouseButtonDown(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		return 0x00000001 & GetAsyncKeyState(MouseCodeToVirtualKeyCode(mouse_code));
	}

	std::array<int, 2> Input::GetMousePos()
	{
		AP_PROFILE_FN();
		POINT point;
		GetCursorPos(&point);
		return std::array<int, 2>({ (int)point.x, (int)point.y });
	}

	int Input::GetMouseX()
	{
		AP_PROFILE_FN();
		return GetMousePos()[0];
	}

	int Input::GetMouseY()
	{
		AP_PROFILE_FN();
		return GetMousePos()[1];
	}


	int KeyCodeToVirtualKeyCode(KeyCode key_code)
	{
		AP_PROFILE_FN();
		switch (key_code)
		{
		case A::KeyCode::Unknown:
			break;
		case A::KeyCode::Space:
			return VK_SPACE;
		case A::KeyCode::DoubleQuotes:
			return VK_OEM_7;
		case A::KeyCode::NumberSign:
			return VK_OEM_5;
		case A::KeyCode::SingleQuote:
			return VK_OEM_7;
		case A::KeyCode::Comma:
			return VK_OEM_COMMA;
		case A::KeyCode::Hyphen:
			return VK_OEM_MINUS;
		case A::KeyCode::Dot:
			return VK_OEM_PERIOD;
		case A::KeyCode::Slash:
			return VK_OEM_2;
		case A::KeyCode::Num0:
			return 0x30;
		case A::KeyCode::Num1:
			return 0x31;
		case A::KeyCode::Num2:
			return 0x32;
		case A::KeyCode::Num3:
			return 0x33;
		case A::KeyCode::Num4:
			return 0x34;
		case A::KeyCode::Num5:
			return 0x35;
		case A::KeyCode::Num6:
			return 0x36;
		case A::KeyCode::Num7:
			return 0x37;
		case A::KeyCode::Num8:
			return 0x38;
		case A::KeyCode::Num9:
			return 0x39;
		case A::KeyCode::Semicolon:
			return VK_OEM_1;
		case A::KeyCode::Equal:
			return VK_OEM_PLUS;
		case A::KeyCode::A:
			return 0x41;
		case A::KeyCode::B:
			return 0x42;
		case A::KeyCode::C:
			return 0x43;
		case A::KeyCode::D:
			return 0x44;
		case A::KeyCode::E:
			return 0x45;
		case A::KeyCode::F:
			return 0x46;
		case A::KeyCode::G:
			return 0x47;
		case A::KeyCode::H:
			return 0x48;
		case A::KeyCode::I:
			return 0x49;
		case A::KeyCode::J:
			return 0x4A;
		case A::KeyCode::K:
			return 0x4B;
		case A::KeyCode::L:
			return 0x4C;
		case A::KeyCode::M:
			return 0x4D;
		case A::KeyCode::N:
			return 0x4E;
		case A::KeyCode::O:
			return 0x4F;
		case A::KeyCode::P:
			return 0x50;
		case A::KeyCode::Q:
			return 0x51;
		case A::KeyCode::R:
			return 0x52;
		case A::KeyCode::S:
			return 0x53;
		case A::KeyCode::T:
			return 0x54;
		case A::KeyCode::U:
			return 0x55;
		case A::KeyCode::V:
			return 0x56;
		case A::KeyCode::W:
			return 0x57;
		case A::KeyCode::X:
			return 0x58;
		case A::KeyCode::Y:
			return 0x59;
		case A::KeyCode::Z:
			return 0x5A;
		case A::KeyCode::OpenSquareBracket:
			return VK_OEM_4;
		case A::KeyCode::Backslash:
			return VK_OEM_5;
		case A::KeyCode::CloseSquareBracket:
			return VK_OEM_6;
		case A::KeyCode::Grave:
			return VK_OEM_8;
		case A::KeyCode::Escape:
			return VK_ESCAPE;
		case A::KeyCode::Enter:
			return VK_RETURN;
		case A::KeyCode::Tab:
			return VK_TAB;
		case A::KeyCode::Backspace:
			return VK_BACK;
		case A::KeyCode::Insert:
			return VK_INSERT;
		case A::KeyCode::Delete:
			return VK_DELETE;
		case A::KeyCode::Right:
			return VK_RIGHT;
		case A::KeyCode::Left:
			return VK_LEFT;
		case A::KeyCode::Down:
			return VK_DOWN;
		case A::KeyCode::Up:
			return VK_UP;
		case A::KeyCode::PageUp:
			return VK_PRIOR;
		case A::KeyCode::PageDown:
			return VK_NEXT;
		case A::KeyCode::Home:
			return VK_HOME;
		case A::KeyCode::End:
			return VK_END;
		case A::KeyCode::CapsLock:
			return VK_CAPITAL;
		case A::KeyCode::ScrollLock:
			return VK_SCROLL;
		case A::KeyCode::NumLock:
			return VK_NUMLOCK;
		case A::KeyCode::PrintScreen:
			return VK_SNAPSHOT;
		case A::KeyCode::Pause:
			return VK_PAUSE;
		case A::KeyCode::Break:
			return VK_CANCEL;
		case A::KeyCode::F1:
			return VK_F1;
		case A::KeyCode::F2:
			return VK_F2;
		case A::KeyCode::F3:
			return VK_F3;
		case A::KeyCode::F4:
			return VK_F4;
		case A::KeyCode::F5:
			return VK_F5;
		case A::KeyCode::F6:
			return VK_F6;
		case A::KeyCode::F7:
			return VK_F7;
		case A::KeyCode::F8:
			return VK_F8;
		case A::KeyCode::F9:
			return VK_F9;
		case A::KeyCode::F10:
			return VK_F10;
		case A::KeyCode::F11:
			return VK_F11;
		case A::KeyCode::F12:
			return VK_F12;
		case A::KeyCode::F13:
			return VK_F13;
		case A::KeyCode::F14:
			return VK_F14;
		case A::KeyCode::F15:
			return VK_F15;
		case A::KeyCode::F16:
			return VK_F16;
		case A::KeyCode::F17:
			return VK_F17;
		case A::KeyCode::F18:
			return VK_F18;
		case A::KeyCode::F19:
			return VK_F19;
		case A::KeyCode::F20:
			return VK_F20;
		case A::KeyCode::F21:
			return VK_F21;
		case A::KeyCode::F22:
			return VK_F22;
		case A::KeyCode::F23:
			return VK_F23;
		case A::KeyCode::F24:
			return VK_F24;
		case A::KeyCode::F25:
			break;
		case A::KeyCode::Numpad0:
			return VK_NUMPAD0;
		case A::KeyCode::Numpad1:
			return VK_NUMPAD1;
		case A::KeyCode::Numpad2:
			return VK_NUMPAD2;
		case A::KeyCode::Numpad3:
			return VK_NUMPAD3;
		case A::KeyCode::Numpad4:
			return VK_NUMPAD4;
		case A::KeyCode::Numpad5:
			return VK_NUMPAD5;
		case A::KeyCode::Numpad6:
			return VK_NUMPAD6;
		case A::KeyCode::Numpad7:
			return VK_NUMPAD7;
		case A::KeyCode::Numpad8:
			return VK_NUMPAD8;
		case A::KeyCode::Numpad9:
			return VK_NUMPAD9;
		case A::KeyCode::NumpadDecimal:
			return VK_DECIMAL;
		case A::KeyCode::NumpadDivide:
			return VK_DIVIDE;
		case A::KeyCode::NumpadMultiply:
			return VK_MULTIPLY;
		case A::KeyCode::NumpadSubtract:
			return VK_SUBTRACT;
		case A::KeyCode::NumpadPlus:
			return VK_ADD;
		case A::KeyCode::NumpadEnter:
			return VK_RETURN;
		case A::KeyCode::NumpadEqual:
			break;
		case A::KeyCode::LeftShift:
			return VK_LSHIFT;
		case A::KeyCode::LeftControl:
			return VK_LCONTROL;
		case A::KeyCode::LeftAlt:
			return VK_LMENU;
		case A::KeyCode::LeftSuper:
			return VK_LWIN;
		case A::KeyCode::RightShift:
			return VK_RSHIFT;
		case A::KeyCode::RightControl:
			return VK_RCONTROL;
		case A::KeyCode::RightAlt:
			return VK_RMENU;
		case A::KeyCode::RightSuper:
			return VK_RWIN;
		case A::KeyCode::Menu:
			return VK_APPS;
		default:
			break;
		}
		AP_CRIT_C("Key not supported: {0}\tKeyCode: {1}", KeyCodeToString(key_code), key_code);
		return 0;
	}

	int MouseCodeToVirtualKeyCode(MouseCode mouse_code)
	{
		AP_PROFILE_FN();
		switch (mouse_code)
		{
		case A::MouseCode::Unknown:
			break;
		case A::MouseCode::Left:
			return VK_LBUTTON;
		case A::MouseCode::Right:
			return VK_RBUTTON;
		case A::MouseCode::Middle:
			return VK_MBUTTON;
		case A::MouseCode::X1:
			return VK_XBUTTON1;
		case A::MouseCode::X2:
			return VK_XBUTTON2;
		default:
			break;
		}
		AP_CRIT_C("MouseButton not supported: {0}\tMouseCode: {1}", MouseCodeToString(mouse_code), mouse_code);
		return 0;
	}

}