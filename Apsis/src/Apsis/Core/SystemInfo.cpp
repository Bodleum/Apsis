#include "apch.h"
#include "SystemInfo.h"

namespace A {

	PlatformType SystemInfo::s_Platform = Platform::Unknown;
	RendererAPI SystemInfo::s_RendererAPI = RendererAPI::Unknown;
	Unique<SystemInfo> SystemInfo::s_Instance = nullptr;

	Unique<SystemInfo>& SystemInfo::Create()
	{
		AP_PROFILE_FN();
		s_Instance = MakeUnique<SystemInfo>();
		AP_TRACE_C("Created SystemInfo");
		return s_Instance;
	}

	SystemInfo::SystemInfo()
	{
		AP_PROFILE_FN();
		#if defined(AP_PLATFORM_WIN)
			s_Platform = Platform::Windows;
			s_RendererAPI = RendererAPI::OpenGL;
		#elif defined(AP_PLATFORM_SIMULATOR)
			s_Platform = Platform::Simulator;
		#elif defined(AP_PLATFORM_IPHONE)
			s_Platform = Platform::iPhone;
		#elif defined(AP_PLATFORM_OSX)
			s_Platfom = Platform::OSX;
		#elif defined(AP_PLATFORM_LINUX)
			s_Platfom = Platform::Linux;
		#elif defined(AP_PLATFORM_UNIX)
			s_Platfom = Platform::Unix;
		#elif defined(AP_PLATFORM_POSIX)
			s_Platfom = Platform::POSIX;
		#endif // AP_PLATFORM_X
	}

}