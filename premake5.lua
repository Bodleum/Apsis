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
		defines "AP_PLATFORM_WIN"
		system "Windows"
		architecture "x86_64"

group "TestProjects"
	include "TestProjects/Tetris"

group "Dependancies"
	include "Apsis/dependancies"

group ""
include "Apsis"
include "Sandbox"