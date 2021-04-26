#pragma once
#include "Apsis/Core/Input.h"

struct GLFWwindow;

namespace A {

	class OpenGlInput : public Input
	{
	public:
		// Inherited via Input
		virtual void InitImpl() override;
		virtual bool IsKeyDownImpl(KeyCode key_code) override;
		virtual bool WasKeyDownImpl(KeyCode key_code) override;
		virtual bool IsMouseButtonDownImpl(MouseCode mouse_code) override;
		virtual bool WasMouseButtonDownImpl(MouseCode mouse_code) override;
		virtual std::array<int, 2> GetMousePosImpl() override;
		virtual int GetMouseXImpl() override;
		virtual int GetMouseYImpl() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}