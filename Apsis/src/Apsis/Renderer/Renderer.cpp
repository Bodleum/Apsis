#include "apch.h"
#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"

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