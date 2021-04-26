#pragma once
#include "Apsis/Renderer/RendererAPI.h"

namespace A {

	class SystemInfo
	{
	public:
		SystemInfo();
		virtual ~SystemInfo() = default;
		static Unique<SystemInfo>& Create();

		static const PlatformType GetPlatform() { return s_Platform; }
		static const RendererAPI GetRendererAPI() { return s_RendererAPI; }

	private:

		static PlatformType s_Platform;
		static RendererAPI s_RendererAPI;

		static Unique<SystemInfo> s_Instance;
	};

}