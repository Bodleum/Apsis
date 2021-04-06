#pragma once
#include <iostream>

// Find out platform based on predefined macros by compiler
// from: https://sourceforge.net/p/predef/wiki/OperatingSystems/

#ifdef _WIN64
	#define AP_PLATFORM_WIN
#elif _WIN32
	#error "x86 is not supported, please use x64 instead"
#elif __APPLE__
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
		#define AP_PLATFORM_SIMULATOR
		#error "Not supported"
	#elif TARGET_OS_IPHONE
		#define AP_PLATFORM_IPHONE
		#error "Not supported"
	#else
		#define TARGET_OS_OSX 1
		#define AP_PLATFORM_OSX
		#error "Not supported"
	#endif
#elif __linux
	#define AP_PLATFORM_LINUX
	#error "Not supported"
#elif __unix // all unices not caught above
	#define AP_PLATFORM_UNIX
	#error "Not supported"
#elif __posix
	#define AP_PLATFORM_POSIX
	#error "Not supported"
#endif

namespace A {

	typedef struct PlatformType
	{
		#ifdef AP_PLATFORM_WIN
			static const bool Windows = true;
		#else
			static const bool Windows = false;
		#endif // AP_PLATFORM_WIN

		#ifdef AP_PLATFORM_SIMULATOR
			static const bool Simulator = true;
		#else
			static const bool Simulator = false;
		#endif // AP_PLATFORM_SIMULATOR

		#ifdef AP_PLATFORM_IPHONE
			static const bool iPhone = true;
		#else
			static const bool iPhone = false;
		#endif // AP_PLATFORM_IPHONE

		#ifdef AP_PLATFORM_OSX
			static const bool OSX = true;
		#else
			static const bool OSX = false;
		#endif // AP_PLATFORM_OSX

		#ifdef AP_PLATFORM_LINUX
			static const bool Linux = true;
		#else
			static const bool Linux = false;
		#endif // AP_PLATFORM_LINUX

		#ifdef AP_PLATFORM_UNIX
			static const bool Unix = true;
		#else
			static const bool Unix = false;
		#endif // AP_PLATFORM_UNIX

		#ifdef AP_PLATFORM_POSIX
			static const bool POSIX = true;
		#else
			static const bool POSIX = false;
		#endif // AP_PLATFORM_POSIX
	} Platform;


	/*
	std::ostream& operator<<(std::ostream& os, PlatformType& plat)
	{
		if (A::Platform::Windows)
			os << "Windows (x64)";

		else if (A::Platform::Simulator)
			os << "Simulator";

		else if (A::Platform::iPhone)
			os << "iPhone";

		else if (A::Platform::OSX)
			os << "OSX";

		else if (A::Platform::Linux)
			os << "Linux";

		else if (A::Platform::Unix)
			os << "Unix";

		else if (A::Platform::POSIX)
			os << "POSIX";

		else
			os << "Unknown";

		return os;
	}
	*/

}