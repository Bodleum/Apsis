#include "apch.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace A {

	OpenGLRenderer::OpenGLRenderer()
	{
		AP_PROFILE_FN();
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		AP_PROFILE_FN();
	}

	bool OpenGLRenderer::InitImpl(Unique<Window>& window)
	{
		AP_PROFILE_FN();

		{// Create vertex buffer
			AP_PROFILE_SCOPE("Create vertex buffer");
			float positions[6] =
			{
				-0.5f, -0.5f,
				 0.0f,  0.5f,
				 0.5f, -0.5f
			};
			glGenBuffers(1, &m_VertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
		}

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