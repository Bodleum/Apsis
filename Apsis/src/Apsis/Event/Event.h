#pragma once
#include "apch.h"		// sstream
#include "Apsis/Core/Input/InputCodes.h"

namespace A {

	class LocalDispatcher;

	enum class EventType
	{
		Unknown = 0,
		Test,
		Message,

		// Mouse
		MouseButtonDown,
		MouseButtonUp,
		MouseMove,
		MouseWheel,

		// Keyboard
		KeyDown,
		KeyUp,
		KeyChar,

		// Window
		MouseEnter,
		MouseExit,
		WindowClose,
		WindowDestroy,
		WindowResize,
		WindowPaint,

		// App
		AppQuit
	};

	#define AP_SET_EVENT_TYPE(type) static EventType GetTypeS() { return EventType::type; } \
									virtual EventType GetType() const override { return EventType::type; }

	struct Event
	{
		virtual EventType GetType() const = 0;
		virtual std::string GetString() const = 0;
		inline bool IsComplete() const { return m_Complete; }

		friend class LocalDispatcher;

	protected:
		bool m_Complete = false;
	};

	class TestEvent : public Event
	{
	public:
		TestEvent(const std::string& msg)
			: m_Message(msg)
		{
		}

		inline std::string GetMessage() { return m_Message; }
		virtual std::string GetString() const override { return m_Message; }
		AP_SET_EVENT_TYPE(Test)

	private:
		std::string m_Message;
	};

	class Message : public Event
	{
	public:
		Message(const std::string& msg)
			: Msg(msg)
		{
		}

		virtual std::string GetString() const override { return Msg; }
		AP_SET_EVENT_TYPE(Message)

		std::string Msg;
	};

	// Operator overloading for easy comparison
	inline bool operator == (const Message& msg, const char* string) { return msg.Msg == string; }

	//  --- Mouse   ---
	class MouseEvent : public Event
	{
	public:
		MouseEvent(int x, int y)
			: m_MouseX(x), m_MouseY(y)
		{
		}

		inline int GetX() const { return m_MouseX; }
		inline int GetY() const { return m_MouseY; }

	protected:
		int m_MouseX;
		int m_MouseY;
	};

	class MouseButtonDownEvent : public MouseEvent
	{
	public:
		MouseButtonDownEvent(int x, int y, MouseCode button)
			: MouseEvent(x, y), m_Button(button)
		{
		}

		inline MouseCode GetButton() const { return m_Button; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDown: " << MouseCodeToString(m_Button) << " at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		AP_SET_EVENT_TYPE(MouseButtonDown)

	private:
		MouseCode m_Button;
	};

	class MouseButtonUpEvent : public MouseEvent
	{
	public:
		MouseButtonUpEvent(int x, int y, MouseCode button)
			: MouseEvent(x, y), m_Button(button)
		{
		}

		inline MouseCode GetButton() const { return m_Button; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUp: " << MouseCodeToString(m_Button) << " at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		AP_SET_EVENT_TYPE(MouseButtonUp)

	private:
		MouseCode m_Button;
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(int x, int y)
			: MouseEvent(x, y)
		{
		}

		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseMove at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		AP_SET_EVENT_TYPE(MouseMove)
	};

	class MouseWheelEvent : public MouseEvent
	{
	public:
		MouseWheelEvent(int x, int y, int delta)
			: MouseEvent(x, y), m_Delta(delta)
		{
		}

		inline int GetDelta() const { return m_Delta; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseWheel, Delta: " << m_Delta << " at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		AP_SET_EVENT_TYPE(MouseWheel)

	private:
		int m_Delta;
	};


	// ---   Keyboard   ---
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(KeyCode key_code)
			: m_KeyCode(key_code)
		{
		}

		KeyCode m_KeyCode;
	};

	class KeyDownEvent : public KeyEvent
	{
	public:
		KeyDownEvent(KeyCode key_code, bool repeat)
			: KeyEvent(key_code), m_Repeat(repeat)
		{
		}

		inline KeyCode GetKeyCode() const { return m_KeyCode; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << KeyCodeToString(m_KeyCode) << " Down";
			if (m_Repeat)
				ss << "\tRepeat";
			return ss.str();
		}

		AP_SET_EVENT_TYPE(KeyDown)

	private:
		bool m_Repeat;
	};

	class KeyUpEvent : public KeyEvent
	{
	public:
		KeyUpEvent(KeyCode key_code)
			: KeyEvent(key_code)
		{
		}

		inline KeyCode GetKeyCode() const { return m_KeyCode; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << KeyCodeToString(m_KeyCode) << " Up";
			return ss.str();
		}

		AP_SET_EVENT_TYPE(KeyUp)
	};

	class KeyCharEvent : public KeyEvent
	{
	public:
		KeyCharEvent(KeyCode key_code, const char character, bool repeat)
			: KeyEvent(key_code), m_Char(character), m_Repeat(repeat)
		{
		}

		inline const char GetKeyChar() const { return m_Char; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << m_Char << " Char";
			if (m_Repeat)
				ss << "\tRepeat";
			return ss.str();
		}

		AP_SET_EVENT_TYPE(KeyChar)

	private:
		const char m_Char;
		bool m_Repeat;
	};


	// ---   Window   ---
	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent()
		{
		}

		virtual std::string GetString() const override { return "MouseEnter"; }
		AP_SET_EVENT_TYPE(MouseEnter)
	};

	class MouseExitEvent : public Event
	{
	public:
		MouseExitEvent()
		{
		}

		virtual std::string GetString() const override { return "MouseExit"; }
		AP_SET_EVENT_TYPE(MouseExit)
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		virtual std::string GetString() const override { return "WindowClose"; }
		AP_SET_EVENT_TYPE(WindowClose)
	};

	class WindowDestroyEvent : public Event
	{
	public:
		WindowDestroyEvent()
		{
		}

		virtual std::string GetString() const override { return "WindowDestroy"; }
		AP_SET_EVENT_TYPE(WindowDestroy)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
		}

		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "WindowResize: " << m_Width << 'x' << m_Height;
			return ss.str();
		}

		AP_SET_EVENT_TYPE(WindowResize)

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowPaintEvent : public Event
	{
	public:
		WindowPaintEvent()
		{
		}

		virtual std::string GetString() const override { return "WindowPaint"; }
		AP_SET_EVENT_TYPE(WindowPaint)
	};


	// ---   App   ---
	class AppQuitEvent : public Event
	{
	public:
		AppQuitEvent()
		{
		}

		virtual std::string GetString() const override { return "AppQuit"; }
		AP_SET_EVENT_TYPE(AppQuit)
	};

	// Printing events
	inline std::ostream& operator<<(std::ostream& os, const Event& evt)
	{
		return os << evt.GetString();
	}

}