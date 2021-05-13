#pragma once

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