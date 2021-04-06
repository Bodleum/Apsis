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
        defines "AP_DEBUG"
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        defines "AP_RELEASE"
        runtime "Release"
        optimize "Full"

    filter { "configurations:Final" }
        defines "AP_FINAL"
        runtime "Release"
        optimize "Full"

    filter { "system:Windows" }
      systemversion "latest"