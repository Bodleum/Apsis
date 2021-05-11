#include "apch.h"
#include "SystemInfo.h"

namespace A {

	#if defined(AP_PLATFORM_WIN)
		const PlatformType SystemInfo::Platform = PlatformType::Windows;
	#elif defined(AP_PLATFORM_SIMULATOR)
		const PlatformType SystemInfo::Platform = PlatformType::Simulator;
	#elif defined(AP_PLATFORM_IPHONE)
		const PlatformType SystemInfo::Platform = PlatformType::iPhone;
	#elif defined(AP_PLATFORM_OSX)
		const PlatformType SystemInfo::Platform = PlatformType::OSX;
	#elif defined(AP_PLATFORM_LINUX)
		const PlatformType SystemInfo::Platform = PlatformType::Linux;
	#elif defined(P_PLATFORM_UNIX)
		const PlatformType SystemInfo::Platform = PlatformType::Unix;
	#elif defined(AP_PLATFORM_POSIX)
		const PlatformType SystemInfo::Platform = PlatformType::POSIX;
	#endif

	
	RendererAPI SystemInfo::RendererAPI = RendererAPI::OpenGL;		// Hard code for now -> only one currently supported

}