project "Apsis"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"src/Apsis.h",
		"src/apch.h",
		"src/apch.cpp",
		"src/Apsis/**.h",
		"src/Apsis/**.cpp",
		"src/OpenGL/**.h",
		"src/OpenGL/**.cpp"
	}

	removefiles
	{
		"src/Apsis/Core/Job/*.h",
		"src/Apsis/Core/Job/*.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/Apsis/dependancies/spdlog/include",
		"%{wks.location}/Apsis/dependancies/eigen-3.3.9",
		"%{wks.location}/Apsis/dependancies/glad/include",
		"%{wks.location}/Apsis/dependancies/GLFW/include",
		"%{wks.location}/Apsis/dependancies/stb_image"
	}

	links
	{
		"spdlog",
		"glad",
		"GLFW",
		"stb_image"
	}

	pchheader "apch.h"
	pchsource "src/apch.cpp"

	filter { "configurations:Debug" }
		defines "AP_DEBUG"
		runtime "Debug"
		symbols "On"
		ignoredefaultlibraries { "libcmt", "msvcrt", "msvcrtd"}
		
		filter { "configurations:Release" }
		defines "AP_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "Full"
		ignoredefaultlibraries { "msvcrt", "libcmtd", "msvcrtd"}
		
		filter { "configurations:Final" }
		defines "AP_FINAL"
		runtime "Release"
		optimize "Full"
		ignoredefaultlibraries { "msvcrt", "libcmtd", "msvcrtd"}

	filter { "system:Windows" }
		systemversion "latest"
		files
		{
			"src/Windows/**.h",
			"src/Windows/**.cpp"
		}