project "Tetirs"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
	objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

	files
	{
		"**.h",
		"**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Apsis/src",
		"%{wks.location}/Apsis/dependancies/spdlog/include",
	}

	links
	{
		"Apsis"
	}

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
		entrypoint "wWinMainCRTStartup"