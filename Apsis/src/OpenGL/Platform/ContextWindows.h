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

		MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
	}

}