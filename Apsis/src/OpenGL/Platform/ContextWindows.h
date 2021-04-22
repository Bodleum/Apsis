#pragma once
#include "Apsis/Core/Window.h"

#include <GL/GL.h>
#pragma comment (lib, "opengl32.lib")

namespace A {

	using OpenGLContext = HGLRC;

	void CreateOpenGLContextWin(OpenGLContext* context, Unique<Window>& window, bool make_current)
	{
		HDC deviceContextHandle = window->GetDeviceContextHandle();
		*context = wglCreateContext(deviceContextHandle);
		if (make_current) wglMakeCurrent(deviceContextHandle , *context);
	}

	void RecreateOpenGLContextWin(OpenGLContext* context, Unique<Window>& window, bool make_current)
	{
		wglDeleteContext(*context);

		/*
		* Set new context with extensions and attributes
		*/

		HDC deviceContextHandle = window->GetDeviceContextHandle();
		*context = wglCreateContext(deviceContextHandle);
		if (make_current) wglMakeCurrent(deviceContextHandle, *context);
	}

}