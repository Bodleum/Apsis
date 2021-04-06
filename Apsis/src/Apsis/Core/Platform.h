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
		#error "Not supported"
	#elif TARGET_OS_IPHONE
		#error "Not supported"
	#else
		#define TARGET_OS_OSX 1
		#error "Not supported"
	#endif
#elif __linux
	#error "Not supported"
#elif __unix // all unices not caught above
	#error "Not supported"
#elif __posix
	#error "Not supported"
#endif