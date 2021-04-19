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

		// Inherited via Renderer
		virtual bool InitImpl(void* window_handle) override;
		virtual inline void ClearImpl() override { m_RenderTarget->Clear(D2D1::ColorF(m_ClearColor.x(), m_ClearColor.y(), m_ClearColor.z())); }
		virtual inline void SetClearColorImpl(Eigen::Vector4f& col) override { m_ClearColor = col; }
		virtual void DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) override;

		virtual inline void BeginDrawImpl() override { m_RenderTarget->BeginDraw(); }
		virtual inline void EndDrawImpl() override { m_RenderTarget->EndDraw(); }

	private:
		ID2D1Factory* m_Factory;
		ID2D1HwndRenderTarget* m_RenderTarget;
		ID2D1SolidColorBrush* m_SolidColorBrush;

	};

}