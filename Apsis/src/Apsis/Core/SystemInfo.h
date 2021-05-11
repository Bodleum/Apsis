#pragma once
#include "Apsis/Core/Platform.h"
#include "Apsis/Renderer/RendererAPI.h"

namespace A {

	enum class PlatformType : unsigned short;

	struct SystemInfo
	{
		static PlatformType Platform;
		static RendererAPI RendererAPI;
	};

}