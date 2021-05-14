#include "apch.h"
#include "Event.h"
	//#include "Apsis/Core/Input/InputCodes.h"

namespace A {

	std::string MouseButtonDownEvent::GetString() const
	{
		std::stringstream ss;
		ss << "MouseButtonDown: " << MouseCodeToString(m_Button) << " at " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	std::string MouseButtonUpEvent::GetString() const
	{
		std::stringstream ss;
		ss << "MouseButtonUp: " << MouseCodeToString(m_Button) << " at " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	std::string MouseMoveEvent::GetString() const
	{
		std::stringstream ss;
		ss << "MouseMove at " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	std::string MouseWheelEvent::GetString() const
	{
		std::stringstream ss;
		ss << "MouseWheel, Delta: " << m_Delta << " at " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	std::string KeyDownEvent::GetString() const
	{
		std::stringstream ss;
		ss << KeyCodeToString(m_KeyCode) << " Down";
		if (m_Repeat)
			ss << "\tRepeat";
		return ss.str();
	}

	std::string KeyUpEvent::GetString() const
	{
		std::stringstream ss;
		ss << KeyCodeToString(m_KeyCode) << " Up";
		return ss.str();
	}

	std::string KeyCharEvent::GetString() const
	{
		std::stringstream ss;
		ss << m_Char << " Char";
		if (m_Repeat)
			ss << "\tRepeat";
		return ss.str();
	}

	std::string WindowResizeEvent::GetString() const
	{
		std::stringstream ss;
		ss << "WindowResize: " << m_Width << 'x' << m_Height;
		return ss.str();
	}

}