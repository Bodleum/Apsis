#pragma once
#include "Apsis/Core/Window.h"
#include "Apsis/Core/Input/InputCodes.h"

struct GLFWwindow;

namespace A {


	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, std::string name);
		virtual ~OpenGLWindow();

		// Inherited via Window
		virtual void Destroy() override;
		virtual bool PollEvents() const override;
		virtual void* GetHandle() const override;
		virtual const HDC GetDeviceContextHandle() const override;

	private:
		GLFWwindow* m_WindowHandle;
		std::string m_Name;
	};

}