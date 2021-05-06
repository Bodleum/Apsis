project "spdlog"
	location "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"spdlog/include/**.h",
		"spdlog/src/**.cpp"
	}

	includedirs
	{
		"spdlog/src",
		"spdlog/include"
	}

	defines
	{
		"SPDLOG_COMPILED_LIB"
	}

	filter { "configurations:Debug" }
		runtime "Debug"
		symbols "On"

	filter { "configurations:Release" }
		runtime "Release"
		optimize "Full"

	filter { "system:Windows" }
		systemversion "latest"


project "glad"
	location "glad"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"glad/include/**.h",
		"glad/src/**.c"
	}

	includedirs
	{
		"glad/src",
		"glad/include"
	}

	filter { "configurations:Debug" }
		runtime "Debug"
		symbols "On"

	filter { "configurations:Release" }
		runtime "Release"
		optimize "Full"

	filter { "system:Windows" }
		systemversion "latest"


project "GLFW"
	location "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"GLFW/include/GLFW/glfw3.h",
		"GLFW/include/GLFW/glfw3native.h",
		"GLFW/src/glfw_config.h",
		"GLFW/src/context.c",
		"GLFW/src/init.c",
		"GLFW/src/input.c",
		"GLFW/src/monitor.c",
		"GLFW/src/vulkan.c",
		"GLFW/src/window.c"
	}

	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			"GLFW/src/x11_init.c",
			"GLFW/src/x11_monitor.c",
			"GLFW/src/x11_window.c",
			"GLFW/src/xkb_unicode.c",
			"GLFW/src/posix_time.c",
			"GLFW/src/posix_thread.c",
			"GLFW/src/glx_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c",
			"GLFW/src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"GLFW/src/win32_init.c",
			"GLFW/src/win32_joystick.c",
			"GLFW/src/win32_monitor.c",
			"GLFW/src/win32_time.c",
			"GLFW/src/win32_thread.c",
			"GLFW/src/win32_window.c",
			"GLFW/src/wgl_context.c",
			"GLFW/src/egl_context.c",
			"GLFW/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"


project "stb_image"
	location "stb_image"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"stb_image/**.h",
		"stb_image/**.cpp"
	}

	includedirs
	{
		"stb_image"
	}

	filter { "configurations:Debug" }
		runtime "Debug"
		symbols "On"

	filter { "configurations:Release" }
		runtime "Release"
		optimize "Full"

	filter { "system:Windows" }
		systemversion "latest"