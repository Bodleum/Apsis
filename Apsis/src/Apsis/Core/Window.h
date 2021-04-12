#pragma once
#include <memory>

namespace A {

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		static std::shared_ptr<Window> Create();
	};

}