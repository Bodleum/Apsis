project "Apsis"
    kind "StaticLib"
    language "C++"

    targetdir ("%{wks.location}/bin/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")
    objdir ("%{wks.location}/int/%{cfg.system}_%{cfg.buildcfg}/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "dependancies/spdlog/include"
    }

    pchheader "apch.h"
    pchsource "src/apch.cpp"

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
