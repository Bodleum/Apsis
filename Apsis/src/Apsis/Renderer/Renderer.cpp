#include "apch.h"
#include "Renderer.h"
	//#include "Apsis/Core/SystemInfo.h"
	//#include "Apsis/Renderer/Cam.h"
	//	#include <Eigen/Core>
	//	#include <Eigen/Geometry>
	//	#include <Eigen/Dense>
	//#include "Apsis/Renderer/Shader.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>
	//#include "Apsis/Renderer/Texture.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>

#include "OpenGL/OpenGLRenderer.h"
	//#include "Apsis/Core/Window.h"
	//#include "Apsis/Renderer/Renderer.h"
	//	#include "Apsis/Core/SystemInfo.h"
	//	#include "Apsis/Renderer/Cam.h"
	//		#include <Eigen/Core>
	//		#include <Eigen/Geometry>
	//		#include <Eigen/Dense>
	//	#include "Apsis/Renderer/Shader.h"
	//		#include "Apsis/Core/Core.h"
	//			#include <memory>
	//			#include <chrono>
	//	#include "Apsis/Renderer/Texture.h"
	//		#include "Apsis/Core/Core.h"
	//			#include <memory>
	//			#include <chrono>

#if defined(AP_PLATFORM_WIN)
	#include "Windows/Direct2D/Direct2DRenderer.h"
#endif // defined(AP_PLATFORM_WIN)

namespace A {

	Shared<GraphicsResources> Renderer::s_GraphicsResources = MakeShared<GraphicsResources>();
	Shared<Cam> Renderer::s_Cam = nullptr;
	Shared<Renderer> Renderer::s_Instance = nullptr;

	Shared<Renderer> Renderer::Create(Unique<Window>& window)
	{
		AP_PROFILE_FN();

		s_GraphicsResources->RendererAPI = SystemInfo::RendererAPI;	// Update
		switch (s_GraphicsResources->RendererAPI)
		{
		case A::RendererAPI::Direct2D:
			s_Instance = MakeShared<Direct2DRenderer>();
			{// Init renderer
				AP_PROFILE_SCOPE("Init renderer");
				bool res = Renderer::Init(window);
				if (!res)
				{
					AP_CRIT_C("Failed to initialise renderer!");
					break;
				}
				AP_INFO_C("Initialised Direct2D renderer");
			}
			return s_Instance;
		case A::RendererAPI::OpenGL:
			s_Instance = MakeShared<OpenGLRenderer>();
			{// Init renderer
				AP_PROFILE_SCOPE("Init renderer");
				bool res = Renderer::Init(window);
				if (!res)
				{
					AP_CRIT_C("Failed to initialise renderer!");
					break;
				}
				AP_INFO_C("Initialised OpenGL renderer");
			}
			return s_Instance;
		default:
			break;
		}
		return nullptr;
	}

}