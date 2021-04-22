#include "apch.h"
#include "OpenGLRenderer.h"

#ifdef AP_PLATFORM_WIN
	#include "OpenGL/Platform/ContextWindows.h"
#endif // AP_PLATFORM_WIN


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

	void OpenGLRenderer::CreateContext(OpenGLContext* context, Unique<Window>& window)
	{
		AP_PROFILE_FN();

		#ifdef AP_PLATFORM_WIN
			CreateOpenGLContextWin(context, window);
		#endif // AP_PLATFORM_WIN

	}

	bool OpenGLRenderer::InitImpl(Unique<Window>& window)
	{
		AP_PROFILE_FN();

		CreateContext(&m_Context, window);
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