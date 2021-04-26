#include "apch.h"
#include "OpenGLWindow.h"

//#include "Apsis/Event/Event.h"		Included in EventDispatcher.h
#include "Apsis/Event/EventDispatcher.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Translators.h"

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

}