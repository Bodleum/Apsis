#pragma once
#include "apch.h"		// sstream
#include "Apsis/Core/InputCodes.h"

namespace A {

	enum class EventType
	{
		Unknown = 0,
		Test,

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
		WindowClose,
		WindowDestroy,
		WindowResize,

		// App
		AppQuit
	};

	struct Event
	{
		virtual EventType GetType() const { return EventType::Unknown; };
		virtual std::string GetString() const { return ""; }
		inline bool IsComplete() const { return m_Complete; }

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
		virtual EventType GetType() const override { return EventType::Test; }
		virtual std::string GetString() const override { return m_Message; }

	private:
		std::string m_Message;
	};

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

		virtual EventType GetType() const override { return EventType::MouseButtonDown; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonDown: " << MouseCodeToString(m_Button) << " at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

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

		virtual EventType GetType() const override { return EventType::MouseButtonUp; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonUp: " << MouseCodeToString(m_Button) << " at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

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

		virtual EventType GetType() const override { return EventType::MouseMove; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseMove at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	};

	class MouseWheelEvent : public MouseEvent
	{
	public:
		MouseWheelEvent(int x, int y, int delta)
			: MouseEvent(x, y), m_Delta(delta)
		{
		}

		inline int GetDelta() const { return m_Delta; }

		virtual EventType GetType() const override { return EventType::MouseWheel; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "MouseWheel, Delta: " << m_Delta << " at " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

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

		virtual EventType GetType() const override { return EventType::KeyDown; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "KeyDown: " << KeyCodeToString(m_KeyCode);
			return ss.str();
		}

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

		virtual EventType GetType() const override { return EventType::KeyUp; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "KeyUp: " << KeyCodeToString(m_KeyCode);
			return ss.str();
		}
	};

	class KeyCharEvent : public KeyEvent
	{
	public:
		KeyCharEvent(KeyCode key_code, char character, bool repeat)
			: KeyEvent(key_code), m_Char(character), m_Repeat(repeat)
		{
		}

		inline char GetKeyChar() const { return m_Char; }

		virtual EventType GetType() const override { return EventType::KeyChar; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "KeyChar: " << m_Char;
			return ss.str();
		}

	private:
		char m_Char;
		bool m_Repeat;
	};


	// ---   Window   ---
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		virtual EventType GetType() const override { return EventType::WindowClose; }
		virtual std::string GetString() const override { return "WindowClose"; }
	};

	class WindowDestroyEvent : public Event
	{
	public:
		WindowDestroyEvent()
		{
		}

		virtual EventType GetType() const override { return EventType::WindowDestroy; }
		virtual std::string GetString() const override { return "WindowDestroy"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
		}

		virtual EventType GetType() const override { return EventType::WindowResize; }
		virtual std::string GetString() const override
		{
			std::stringstream ss;
			ss << "WindowResize: " << m_Width << 'x' << m_Height;
			return ss.str();
		}

	private:
		unsigned int m_Width, m_Height;
	};


	// ---   App   ---
	class AppQuitEvent : public Event
	{
	public:
		AppQuitEvent()
		{
		}

		virtual EventType GetType() const override { return EventType::AppQuit; }
		virtual std::string GetString() const override { return "AppQuit"; }
	};

	// Printing events
	inline std::ostream& operator<<(std::ostream& os, const Event& evt)
	{
		return os << evt.GetString();
	}

}