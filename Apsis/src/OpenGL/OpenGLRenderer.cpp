#include "apch.h"
#include "OpenGLRenderer.h"

namespace A {

	OpenGLRenderer::OpenGLRenderer()
		: m_Context(nullptr)
	{
		AP_PROFILE_FN();
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::CreateContext(OpenGLContext* context, Unique<Window>& window, bool make_current)
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::RecreateContext(OpenGLContext* context, Unique<Window>& window, bool make_current)
	{
		AP_PROFILE_FN();
	}
	bool OpenGLRenderer::InitImpl(Unique<Window>& window)
	{
		AP_PROFILE_FN();
		return true;
	}

	void OpenGLRenderer::BeginDrawImpl()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::EndDrawImpl()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::ClearImpl()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::SetClearColorImpl(Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::OnResizeImpl()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::DrawRectImpl(Eigen::Vector2i& position, float width, float height, Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
	}

}