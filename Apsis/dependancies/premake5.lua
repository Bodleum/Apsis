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