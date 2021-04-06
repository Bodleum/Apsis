workspace "Apsis"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Final"
    }

    platforms
    {
        "Win64"
    }

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"

include "Apsis"
include "Sandbox"