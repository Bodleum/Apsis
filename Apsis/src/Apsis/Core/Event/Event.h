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

	protected:
		bool Complete = false;
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

	private:
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

}