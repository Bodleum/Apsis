#include "apch.h"
#include "Direct2DRenderer.h"

namespace A {

	Direct2DRenderer::Direct2DRenderer()
		: m_Factory(NULL), m_RenderTarget(NULL)
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
	}

	bool Direct2DRenderer::Init(void* window_handle)
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

		return true;
	}

}