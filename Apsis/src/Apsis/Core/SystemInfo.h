#pragma once

namespace A {

	typedef enum class PlatformType : unsigned short
	{
		Unknown = 0,
		Windows,
		Simulator,
		iPhone,
		OSX,
		Linux,
		Uinx,
		POSIX
	} Platform;

	enum class RendererAPI : unsigned short
	{
		Unknown = 0,
		Direct2D,
		OpenGL
	};

	struct SystemInfo
	{
		const static PlatformType Platform;
		static RendererAPI RendererAPI;
	};

}