#pragma once
#include "Apsis/Core/Platform.h"
#include "Apsis/Renderer/RendererAPI.h"

namespace A {

	enum class PlatformType : unsigned short;

	struct SystemInfo
	{
		const static PlatformType Platform;
		static RendererAPI RendererAPI;
	};

}