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
		virtual bool Init(void* window_handle) override;
		virtual inline void Clear() override { m_RenderTarget->Clear(D2D1::ColorF((FLOAT)m_ClearColor.x(), (FLOAT)m_ClearColor.y(), (FLOAT)m_ClearColor.z())); }
		virtual inline void SetClearColor(Eigen::Vector4f& col) override { m_ClearColor = col; }
		virtual void DrawCircle(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) override;

		inline void BeginDraw() { m_RenderTarget->BeginDraw(); }
		inline void EndDraw() { m_RenderTarget->EndDraw(); }

	private:
		ID2D1Factory* m_Factory;
		ID2D1HwndRenderTarget* m_RenderTarget;
		ID2D1SolidColorBrush* m_SolidColorBrush;

	};

}