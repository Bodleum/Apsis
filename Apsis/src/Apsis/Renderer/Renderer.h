#pragma once
#include "apch.h"	// Shared

namespace A {

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual bool Init(void* window_handle) = 0;

		static Shared<Renderer> Create();
	};

}