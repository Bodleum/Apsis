#include "apch.h"
#include "OpenGLRenderer.h"
#include "OpenGLHeaders.h"

namespace A {

	OpenGLRenderer::OpenGLRenderer()
		: m_WindowHandle(nullptr), m_Shader(nullptr)
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

		m_WindowHandle = (GLFWwindow*)window->GetHandle();

		glCreateVertexArrays(1, &m_VertexArrayID);
		glBindVertexArray(m_VertexArrayID);

		{// Create vertex buffer
			AP_PROFILE_SCOPE("Create vertex buffer");
			float positions[3 * 3] =
			{
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};
			glCreateBuffers(1, &m_VertexBufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
			glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_STATIC_DRAW);	// Fill with data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			glEnableVertexAttribArray(0);
		}

		{// Create index buffer
			AP_PROFILE_SCOPE("Create index buffer");
			unsigned int indices[3] = { 0, 1, 2 };
			glCreateBuffers(1, &m_IndexBufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}

		{// Create shader
			AP_PROFILE_SCOPE("Create shader");
			m_Shader = Shader::Create("D:/Dev/C++/Apsis/Apsis/src/Assets/OpenGL/DefaultShader.glsl");
			m_Shader->Bind();
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
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLRenderer::ClearImpl()
	{
		AP_PROFILE_FN();
		glClearColor(m_ClearColor.x(), m_ClearColor.y(), m_ClearColor.z(), m_ClearColor.w());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::SetClearColorImpl(Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
		m_ClearColor = col;
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
		glBindVertexArray(m_VertexArrayID);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}

}