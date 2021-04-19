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
		virtual void OnResizeImpl() override;

		virtual void DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) override;

		virtual inline void BeginDrawImpl() override { if (!m_RenderTarget) { CreateGraphicsResources(); }m_RenderTarget->BeginDraw(); }
		virtual inline void EndDrawImpl() override
		{
			HRESULT res = m_RenderTarget->EndDraw();
			if (FAILED(res) || res == D2DERR_RECREATE_TARGET)
			{
				AP_WARN_C("Graphics device loss");
				ReleaseGraphicsResources();
			}
		}



	private:
		bool CreateGraphicsResources();
		void ReleaseGraphicsResources();
		template <class T>
		inline void SafeRelease(T** ppT) { if (*ppT) { (*ppT)->Release(); *ppT = NULL; } }

		HWND m_WindowHandle;
		ID2D1Factory* m_Factory;
		ID2D1HwndRenderTarget* m_RenderTarget;
		ID2D1SolidColorBrush* m_SolidColorBrush;

	};

}