#include "apch.h"
#include "Direct2DRenderer.h"

namespace A {

	Direct2DRenderer::Direct2DRenderer()
		: m_Factory(NULL), m_RenderTarget(NULL), m_SolidColorBrush(NULL)
	{
		AP_PROFILE_FN();
	}

	Direct2DRenderer::~Direct2DRenderer()
	{
		AP_PROFILE_FN();

		if (m_Factory)
			m_Factory->Release();

		if (m_RenderTarget)
			m_RenderTarget->Release();

		if (m_SolidColorBrush)
			m_SolidColorBrush->Release();
	}

	bool Direct2DRenderer::InitImpl(void* window_handle)
	{
		AP_PROFILE_FN();

		{// Create Direct2D factory
			AP_PROFILE_SCOPE("Create Direct2D factory");
			HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_Factory);
			if (res != S_OK)
			{
				AP_ASSERT_C(false, "Failed to create Direct2D factory! Error: {0}", GetLastError());
				return false;
			}
		}

		{// Create render target
			RECT clientRect;
			AP_PROFILE_SCOPE("Create render target");
			GetClientRect((HWND)window_handle, &clientRect);
			HRESULT res = m_Factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties((HWND)window_handle, D2D1::SizeU(clientRect.right, clientRect.bottom)),
				&m_RenderTarget
			);
			if (res != S_OK)
			{
				AP_ASSERT_C(false, "Failed to create render target! Error: {0}", GetLastError());
				return false;
			}
		}

		{// Create solid color brush
			AP_PROFILE_SCOPE("Create solid color brush");
			HRESULT res = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f), &m_SolidColorBrush);
		}

		return true;
	}

	void Direct2DRenderer::DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col)
	{
		m_SolidColorBrush->SetColor(D2D1::ColorF((FLOAT)m_ClearColor.x(), (FLOAT)m_ClearColor.y(), (FLOAT)m_ClearColor.z()));
		m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(position.x(), position.y()), radius, radius), m_SolidColorBrush, 3.0f);
	}

}