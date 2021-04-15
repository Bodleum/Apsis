#pragma once
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

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

	protected:
		float m_MouseX;
		float m_MouseY;
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
	};

	class KeyCharEvent : public KeyEvent
	{
	public:
		KeyCharEvent(KeyCode key_code, char character)
			: KeyEvent(key_code), m_Char(character)
		{
		}

		inline char GetKeyChar() const { return m_Char; }

		virtual EventType GetType() const override { return EventType::KeyChar; }

	private:
		char m_Char;
	};


	// ---   Window   ---
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		virtual EventType GetType() const override { return EventType::WindowClose; }
	};

	class WindowDestroyEvent : public Event
	{
	public:
		WindowDestroyEvent()
		{
		}

		virtual EventType GetType() const override { return EventType::WindowDestroy; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
		}

		virtual EventType GetType() const override { return EventType::WindowResize; }

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
	};

}