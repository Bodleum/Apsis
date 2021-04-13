#pragma once

namespace A {

	enum class EventType
	{
		Unknown = 0,

		// Mouse
		MouseButtonDown,
		MouseButtonUp,
		MouseMove,
		MouseWheel,

		// Keyboard
		KeyDown,
		KeyUp,
		KeyChar
	};

	struct Event
	{
		virtual EventType GetType() const = 0;
		inline bool IsComplete() const { return m_Complete; }

	protected:
		bool m_Complete = false;
	};

	//  --- Mouse   ---
	class MouseEvent : public Event
	{
	public:
		MouseEvent(float x, float y)
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
		MouseButtonDownEvent(float x, float y, int button)
			: MouseEvent(x, y), m_Button(button)
		{
		}

		inline int GetButton() const { return m_Button; }

		virtual EventType GetType() const override { return EventType::MouseButtonDown; }

	private:
		int m_Button;
	};

	class MouseButtonUpEvent : public MouseEvent
	{
	public:
		MouseButtonUpEvent(float x, float y, int button)
			: MouseEvent(x, y), m_Button(button)
		{
		}

		inline int GetButton() const { return m_Button; }

		virtual EventType GetType() const override { return EventType::MouseButtonUp; }

	private:
		int m_Button;
	};

	class MouseMoveEvent : public MouseEvent
	{
	public:
		MouseMoveEvent(float x, float y)
			: MouseEvent(x, y)
		{
		}

		virtual EventType GetType() const override { return EventType::MouseMove; }
	};

	class MouseWheelEvent : public MouseEvent
	{
	public:
		MouseWheelEvent(float x, float y, int delta)
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
		KeyEvent(int key_code)
			: m_KeyCode(key_code)
		{
		}

		int m_KeyCode;
	};

	class KeyDownEvent : public KeyEvent
	{
	public:
		KeyDownEvent(int key_code, bool repeat)
			: KeyEvent(key_code), m_Repeat(repeat)
		{
		}

		inline int GetKeyCode() const { return m_KeyCode; }

		virtual EventType GetType() const override { return EventType::KeyDown; }

	private:
		bool m_Repeat;
	};

	class KeyUpEvent : public KeyEvent
	{
	public:
		KeyUpEvent(int key_code)
			: KeyEvent(key_code)
		{
		}

		inline int GetKeyCode() const { return m_KeyCode; }

		virtual EventType GetType() const override { return EventType::KeyUp; }
	};

	class KeyCharEvent : public KeyEvent
	{
	public:
		KeyCharEvent(int key_code, char character)
			: KeyEvent(key_code), m_Char(character)
		{
		}

		inline char GetKeyChar() const { return m_Char; }

		virtual EventType GetType() const override { return EventType::KeyChar; }

	private:
		char m_Char;
	};

}