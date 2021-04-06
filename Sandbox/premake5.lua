project "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        runtime "Release"
        optimize "Full"

    filter { "configurations:Final" }
        runtime "Release"
        optimize "Full"

    filter { "system:Windows" }
      systemversion "latest"