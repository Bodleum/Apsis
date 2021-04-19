#include "apch.h"
#include "Direct2DRenderer.h"

namespace A {

	Direct2DRenderer::Direct2DRenderer()
		: m_WindowHandle(NULL), m_Factory(NULL), m_RenderTarget(NULL), m_SolidColorBrush(NULL)
	{
		AP_PROFILE_FN();
	}

	Direct2DRenderer::~Direct2DRenderer()
	{
		AP_PROFILE_FN();
		ReleaseGraphicsResources();
		SafeRelease(&m_Factory);
	}

	bool Direct2DRenderer::InitImpl(void* window_handle)
	{
		AP_PROFILE_FN();

		m_WindowHandle = (HWND)window_handle;

		{// Create Direct2D factory
			AP_PROFILE_SCOPE("Create Direct2D factory");
			HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_Factory);
			if (res != S_OK)
			{
				AP_ASSERT_C(false, "Failed to create Direct2D factory! Error: {0}", GetLastError());
				return false;
			}
			AP_TRACE_C("Created Direct2D factory");
		}

		{// Create graphics resouces
			AP_PROFILE_SCOPE("Create graphics resouces");
			bool res = CreateGraphicsResources();
			if (!res)
			{
				AP_ASSERT_C(false, "Could not create graphics resources");
				return false;
			}
		}

		return true;
	}

	void Direct2DRenderer::DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col)
	{
		m_SolidColorBrush->SetColor(D2D1::ColorF(col.x(), col.y(), col.z()));
		m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(position.x(), position.y()), radius, radius), m_SolidColorBrush, 2.0f);
	}

	bool Direct2DRenderer::CreateGraphicsResources()
	{
		AP_PROFILE_FN();

		{// Create render target
			RECT clientRect;
			AP_PROFILE_SCOPE("Create render target");
			GetClientRect(m_WindowHandle, &clientRect);
			HRESULT res = m_Factory->CreateHwndRenderTarget(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties(m_WindowHandle, D2D1::SizeU(clientRect.right, clientRect.bottom)),
				&m_RenderTarget
			);
			if (res != S_OK)
			{
				AP_ASSERT_C(false, "Failed to create render target! Error: {0}", GetLastError());
				return false;
			}
			AP_TRACE_C("Created Direct2D render target");
		}

		{// Create solid color brush
			AP_PROFILE_SCOPE("Create solid color brush");
			HRESULT res = m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f), &m_SolidColorBrush);
			AP_TRACE_C("Created Direct2D solid color brush");
		}

		return true;
	}

	void Direct2DRenderer::ReleaseGraphicsResources()
	{
		AP_PROFILE_FN();
		SafeRelease(&m_RenderTarget);
		SafeRelease(&m_SolidColorBrush);
	}

}