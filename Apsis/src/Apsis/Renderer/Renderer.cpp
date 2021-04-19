#include "apch.h"
#include "Renderer.h"

#include "Windows/Direct2D/Direct2DRenderer.h"

namespace A {

	Shared<Renderer> Renderer::Create()
	{
		return MakeShared<Direct2DRenderer>();
	}

}