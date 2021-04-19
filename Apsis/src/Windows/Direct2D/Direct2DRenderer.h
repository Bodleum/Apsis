#pragma once
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "Apsis/Renderer/Renderer.h"

namespace A {

	class Direct2DRenderer : public Renderer
	{
	public:
		Direct2DRenderer();
		virtual ~Direct2DRenderer();

		virtual bool Init(void* window_handle) override;

		inline void BeginDraw() { m_RenderTarget->BeginDraw(); }
		inline void EndDraw() { m_RenderTarget->EndDraw(); }

	private:
		ID2D1Factory* m_Factory;
		ID2D1HwndRenderTarget* m_RenderTarget;
	};

}