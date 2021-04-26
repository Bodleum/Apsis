#include "apch.h"
#include "OpenGLWindow.h"

//#include "Apsis/Event/Event.h"		Included in EventDispatcher.h
#include "Apsis/Event/EventDispatcher.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace A {

	OpenGLWindow::OpenGLWindow(unsigned int width, unsigned int height, std::string name)
		: m_WindowHandle(nullptr), m_Width(width), m_Height(height), m_Name(name)
	{
		AP_PROFILE_FN();

		{// Initialise GLFW
			AP_PROFILE_SCOPE("Initialise GLFW");
			int res = glfwInit();
			if (!res)
			{
				AP_CRIT_C("Failed to initialise GLFW, returned {0}", res);
				return;
			}
			AP_TRACE_C("Initialised GLFW");
		}

		glfwSetErrorCallback([](int error, const char* description) { AP_ERROR_C("GLFW error {0}: {1}", error, description); });

		{// Create GLFW window
			AP_PROFILE_SCOPE("Create GLFW window");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			m_WindowHandle = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
			if (!m_WindowHandle)
			{
				AP_CRIT_C("Failed to create glfwWindow");
				glfwTerminate();
				return;
			}
			AP_TRACE_C("Created GLFW window: {0}x{1}", width, height);
		}

		{// Load extensions with glad
			AP_PROFILE_SCOPE("Load extensions with glad");
			glfwMakeContextCurrent(m_WindowHandle);
			int res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			if (!res)
			{
				AP_CRIT_C("Failed to initialise glad");
				return;
			}
			AP_TRACE_C("Initialised glad");
		}

		//Check OpenGL version
		int maj;
		int min;
		glGetIntegerv(GL_MAJOR_VERSION, &maj);
		glGetIntegerv(GL_MINOR_VERSION, &min);
		AP_ASSERT_C(maj > 4 || (maj == 4 && min >= 5), "At least OpenGL version 4.5 is required, current version: {0}.{1}", maj, min);

		{// Set callbacks
			AP_PROFILE_SCOPE("Set callbacks");

			glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					switch (action)
					{
						case GLFW_PRESS:
						{
							EventDispatcher::SendEvent(MakeShared<KeyDownEvent>(GLFWKeyCodeTranslator[key], false));
							break;
						}
						case GLFW_REPEAT:
						{
							EventDispatcher::SendEvent(MakeShared<KeyDownEvent>(GLFWKeyCodeTranslator[key], true));
							break;
						}
						case GLFW_RELEASE:
						{
							EventDispatcher::SendEvent(MakeShared<KeyUpEvent>(GLFWKeyCodeTranslator[key]));
							break;
						}
					}
				}
			);

			glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, unsigned int codepoint)
				{
					EventDispatcher::SendEvent(MakeShared<KeyCharEvent>(GLFWKeyCodeTranslator[codepoint], (char)codepoint, false));
				}
			);

			glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
				{
					switch (action)
					{
						case GLFW_PRESS:
						{
							double x, y;
							glfwGetCursorPos(window, &x, &y);
							EventDispatcher::SendEvent(MakeShared<MouseButtonDownEvent>((int)x, (int)y, GLFWMouseButtonTranslator[button]));
							break;
						}
						case GLFW_RELEASE:
						{
							double x, y;
							glfwGetCursorPos(window, &x, &y);
							EventDispatcher::SendEvent(MakeShared<MouseButtonUpEvent>((int)x, (int)y, GLFWMouseButtonTranslator[button]));
							break;
							break;
						}
					}
				}
			);

			glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double x, double y)
				{
					EventDispatcher::SendEvent(MakeShared<MouseMoveEvent>((int)x, (int)y));
				}
			);

			glfwSetCursorEnterCallback(m_WindowHandle, [](GLFWwindow* window, int entered)
				{
					entered ?	EventDispatcher::SendEvent(MakeShared<MouseEnterEvent>())
						:		EventDispatcher::SendEvent(MakeShared<MouseExitEvent>());
				}
			);

			glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double x_off, double y_off)
				{
					double x, y;
					glfwGetCursorPos(window, &x, &y);
					EventDispatcher::SendEvent(MakeShared<MouseWheelEvent>((int)x, (int)y, (int)x_off));
				}
			);

			glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
				{
					EventDispatcher::SendEvent(MakeShared<WindowResizeEvent>(width, height));
				}
			);

			glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
				{
					EventDispatcher::SendEvent(MakeShared<WindowCloseEvent>());
					EventDispatcher::SendEvent(MakeShared<WindowDestroyEvent>());
				}
			);
		}
	}

	OpenGLWindow::~OpenGLWindow()
	{
		AP_PROFILE_FN();
		glfwDestroyWindow(m_WindowHandle);
		glfwTerminate();
	}

	bool OpenGLWindow::PollEvents() const
	{
		AP_PROFILE_FN();
		glfwPollEvents();
		return true;
	}

	void* OpenGLWindow::GetHandle() const
	{
		AP_PROFILE_FN();
		return m_WindowHandle;
	}

	const HDC OpenGLWindow::GetDeviceContextHandle() const
	{
		AP_PROFILE_FN();
		return HDC();
	}


	std::unordered_map<int, MouseCode> OpenGLWindow::GLFWMouseButtonTranslator =
	{
		{0, Mouse::Left},
		{1, Mouse::Right},
		{2, Mouse::Middle},
		{3, Mouse::X1},
		{4, Mouse::X2}
	};

	std::unordered_map<int, KeyCode> OpenGLWindow::GLFWKeyCodeTranslator =
	{
		{GLFW_KEY_UNKNOWN,			Key::Unknown},
		{GLFW_KEY_SPACE,			Key::Space},
		{GLFW_KEY_APOSTROPHE,		Key::SingleQuote},
		{GLFW_KEY_COMMA,			Key::Comma},
		{GLFW_KEY_MINUS,			Key::Hyphen},
		{GLFW_KEY_PERIOD,			Key::Dot},
		{GLFW_KEY_SLASH,			Key::Slash},
		{GLFW_KEY_0,				Key::Num0},
		{GLFW_KEY_1,				Key::Num1},
		{GLFW_KEY_2,				Key::Num2},
		{GLFW_KEY_3,				Key::Num3},
		{GLFW_KEY_4,				Key::Num4},
		{GLFW_KEY_5,				Key::Num5},
		{GLFW_KEY_6,				Key::Num6},
		{GLFW_KEY_7,				Key::Num7},
		{GLFW_KEY_8,				Key::Num8},
		{GLFW_KEY_9,				Key::Num9},
		{GLFW_KEY_SEMICOLON,		Key::Semicolon},
		{GLFW_KEY_EQUAL,			Key::Equal},
		{GLFW_KEY_A,				Key::A},
		{GLFW_KEY_B,				Key::B},
		{GLFW_KEY_C,				Key::C},
		{GLFW_KEY_D,				Key::D},
		{GLFW_KEY_E,				Key::E},
		{GLFW_KEY_F,				Key::F},
		{GLFW_KEY_G,				Key::G},
		{GLFW_KEY_H,				Key::H},
		{GLFW_KEY_I,				Key::I},
		{GLFW_KEY_J,				Key::J},
		{GLFW_KEY_K,				Key::K},
		{GLFW_KEY_L,				Key::L},
		{GLFW_KEY_M,				Key::M},
		{GLFW_KEY_N,				Key::N},
		{GLFW_KEY_O,				Key::O},
		{GLFW_KEY_P,				Key::P},
		{GLFW_KEY_Q,				Key::Q},
		{GLFW_KEY_R,				Key::R},
		{GLFW_KEY_S,				Key::S},
		{GLFW_KEY_T,				Key::T},
		{GLFW_KEY_U,				Key::U},
		{GLFW_KEY_V,				Key::V},
		{GLFW_KEY_W,				Key::W},
		{GLFW_KEY_X,				Key::X},
		{GLFW_KEY_Y,				Key::Y},
		{GLFW_KEY_Z,				Key::Z},
		{GLFW_KEY_LEFT_BRACKET,		Key::OpenSquareBracket},
		{GLFW_KEY_BACKSLASH,		Key::Backslash},
		{GLFW_KEY_RIGHT_BRACKET,	Key::CloseSquareBracket},
		{GLFW_KEY_GRAVE_ACCENT,		Key::Grave},
		{GLFW_KEY_WORLD_1,			Key::Europe1},
		{GLFW_KEY_WORLD_2,			Key::Europe2},
		{GLFW_KEY_ESCAPE,			Key::Escape},
		{GLFW_KEY_ENTER,			Key::Enter},
		{GLFW_KEY_TAB,				Key::Tab},
		{GLFW_KEY_BACKSPACE,		Key::Backspace},
		{GLFW_KEY_INSERT,			Key::Insert},
		{GLFW_KEY_DELETE,			Key::Delete},
		{GLFW_KEY_RIGHT,			Key::Right},
		{GLFW_KEY_LEFT,				Key::Left},
		{GLFW_KEY_DOWN,				Key::Down},
		{GLFW_KEY_UP,				Key::Up},
		{GLFW_KEY_PAGE_UP,			Key::PageUp},
		{GLFW_KEY_PAGE_DOWN,		Key::PageDown},
		{GLFW_KEY_HOME,				Key::Home},
		{GLFW_KEY_END,				Key::End},
		{GLFW_KEY_CAPS_LOCK,		Key::CapsLock},
		{GLFW_KEY_SCROLL_LOCK,		Key::ScrollLock},
		{GLFW_KEY_NUM_LOCK,			Key::NumLock},
		{GLFW_KEY_PRINT_SCREEN,		Key::PrintScreen},
		{GLFW_KEY_PAUSE,			Key::Pause},
		{GLFW_KEY_F1,				Key::F1},
		{GLFW_KEY_F2,				Key::F2},
		{GLFW_KEY_F3,				Key::F3},
		{GLFW_KEY_F4,				Key::F4},
		{GLFW_KEY_F5,				Key::F5},
		{GLFW_KEY_F6,				Key::F6},
		{GLFW_KEY_F7,				Key::F7},
		{GLFW_KEY_F8,				Key::F8},
		{GLFW_KEY_F9,				Key::F9},
		{GLFW_KEY_F10,				Key::F10},
		{GLFW_KEY_F11,				Key::F11},
		{GLFW_KEY_F12,				Key::F12},
		{GLFW_KEY_F13,				Key::F13},
		{GLFW_KEY_F14,				Key::F14},
		{GLFW_KEY_F15,				Key::F15},
		{GLFW_KEY_F16,				Key::F16},
		{GLFW_KEY_F17,				Key::F17},
		{GLFW_KEY_F18,				Key::F18},
		{GLFW_KEY_F19,				Key::F19},
		{GLFW_KEY_F20,				Key::F20},
		{GLFW_KEY_F21,				Key::F21},
		{GLFW_KEY_F22,				Key::F22},
		{GLFW_KEY_F23,				Key::F23},
		{GLFW_KEY_F24,				Key::F24},
		{GLFW_KEY_F25,				Key::F25},
		{GLFW_KEY_KP_0,				Key::Numpad0},
		{GLFW_KEY_KP_1,				Key::Numpad1},
		{GLFW_KEY_KP_2,				Key::Numpad2},
		{GLFW_KEY_KP_3,				Key::Numpad3},
		{GLFW_KEY_KP_4,				Key::Numpad4},
		{GLFW_KEY_KP_5,				Key::Numpad5},
		{GLFW_KEY_KP_6,				Key::Numpad6},
		{GLFW_KEY_KP_7,				Key::Numpad7},
		{GLFW_KEY_KP_8,				Key::Numpad8},
		{GLFW_KEY_KP_9,				Key::Numpad9},
		{GLFW_KEY_KP_DECIMAL,		Key::NumpadDecimal},
		{GLFW_KEY_KP_DIVIDE,		Key::NumpadDivide},
		{GLFW_KEY_KP_MULTIPLY,		Key::NumpadMultiply},
		{GLFW_KEY_KP_SUBTRACT,		Key::NumpadSubtract},
		{GLFW_KEY_KP_ADD,			Key::NumpadPlus},
		{GLFW_KEY_KP_ENTER,			Key::NumpadEnter},
		{GLFW_KEY_KP_EQUAL,			Key::NumpadEqual},
		{GLFW_KEY_LEFT_SHIFT,		Key::LeftShift},
		{GLFW_KEY_LEFT_CONTROL,		Key::LeftControl},
		{GLFW_KEY_LEFT_ALT,			Key::LeftAlt},
		{GLFW_KEY_LEFT_SUPER,		Key::LeftSuper},
		{GLFW_KEY_RIGHT_SHIFT,		Key::RightShift},
		{GLFW_KEY_RIGHT_CONTROL,	Key::RightControl},
		{GLFW_KEY_RIGHT_ALT,		Key::RightAlt},
		{GLFW_KEY_RIGHT_SUPER,		Key::RightSuper},
		{GLFW_KEY_MENU,				Key::Menu}
	};

}