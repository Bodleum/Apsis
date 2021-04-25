#pragma once
#include "Apsis/Core/Window.h"
#include "Apsis/Core/InputCodes.h"

struct GLFWwindow;

namespace A {


	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, std::string name);
		virtual ~OpenGLWindow();

		// Inherited via Window
		virtual bool PollEvents() const override;
		virtual void* GetHandle() const override;
		virtual const HDC GetDeviceContextHandle() const override;

	private:
		GLFWwindow* m_WindowHandle;
		unsigned int m_Width, m_Height;
		std::string m_Name;

		// Mouse and key codes
		static std::unordered_map<int, MouseCode> GLFWMouseButtonTranslator;
		static std::unordered_map<int, KeyCode> GLFWKeyCodeTranslator;
	};

}