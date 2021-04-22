#include "apch.h"
#include "Renderer.h"

#include "Windows/Direct2D/Direct2DRenderer.h"

namespace A {

	Shared<Renderer> Renderer::s_Instance = Renderer::Create();

	// Set default Renderer API
	#ifdef AP_PLATFORM_WIN
		RendererAPI Renderer::s_RendererAPI = RendererAPI::Direct2D;
	#endif // AP_PLATFORM_WIN

	Shared<Renderer> Renderer::Create()
	{
		switch (s_RendererAPI)
		{
		case A::RendererAPI::Direct2D:
			return MakeShared<Direct2DRenderer>();
		case A::RendererAPI::OpenGL:
			break;
		default:
			break;
		}
		return nullptr;
	}

}