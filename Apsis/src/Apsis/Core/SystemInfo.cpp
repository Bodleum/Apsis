#include "apch.h"
#include "SystemInfo.h"

namespace A {

	#if defined(AP_PLATFORM_WIN)
		PlatformType SystemInfo::Platform = PlatformType::Windows;
	#elif defined(AP_PLATFORM_SIMULATOR)
		PlatformType SystemInfo::Platform = PlatformType::Simulator;
	#elif defined(AP_PLATFORM_IPHONE)
		PlatformType SystemInfo::Platform = PlatformType::iPhone;
	#elif defined(AP_PLATFORM_OSX)
		PlatformType SystemInfo::Platform = PlatformType::OSX;
	#elif defined(AP_PLATFORM_LINUX)
		PlatformType SystemInfo::Platform = PlatformType::Linux;
	#elif defined(P_PLATFORM_UNIX)
		PlatformType SystemInfo::Platform = PlatformType::Unix;
	#elif defined(AP_PLATFORM_POSIX)
		PlatformType SystemInfo::Platform = PlatformType::POSIX;
	#endif

	
	RendererAPI SystemInfo::RendererAPI = RendererAPI::OpenGL;		// Hard code for now -> only one currently supported

}