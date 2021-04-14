#pragma once
#include "Apsis/Core/Main.h"

namespace A {

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		static Unique<Window> Create(MainFnArgs args, const std::string& name = "Window", unsigned int width = 1280, unsigned int height = 720);
	};

}