project "Apsis"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	removefiles
	{
		"src/Apsis/Core/Job/*.h",
		"src/Apsis/Core/Job/*.cpp"
	}

	includedirs
	{
		"src",
		"dependancies/spdlog/include"
	}

	pchheader "apch.h"
	pchsource "src/apch.cpp"

	filter { "configurations:Debug" }
		defines "AP_DEBUG"
		runtime "Debug"
		symbols "On"

	filter { "configurations:Release" }
		defines "AP_RELEASE"
		runtime "Release"
		symbols "On"
		optimize "Full"

	filter { "configurations:Final" }
		defines "AP_FINAL"
		runtime "Release"
		optimize "Full"

	filter { "system:Windows" }
		systemversion "latest"