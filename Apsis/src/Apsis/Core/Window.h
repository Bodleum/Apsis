#pragma once
#include "Apsis/Core/Main.h"

namespace A {

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual bool PollEvents() const = 0;

		virtual unsigned int GetWidth() const { return m_Width; }
		virtual unsigned int GetHeight() const { return m_Height; }
		virtual void* GetHandle() const = 0;

		static Unique<Window> Create(MainFnArgs args, const std::string& name = "Window", unsigned int width = 1280, unsigned int height = 720);

	protected:
		unsigned int m_Width, m_Height;
	};

}