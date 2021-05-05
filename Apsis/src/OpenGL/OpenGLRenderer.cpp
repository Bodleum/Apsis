#include "apch.h"
#include "OpenGLRenderer.h"
#include "OpenGLHeaders.h"

namespace A {

	OpenGLRenderer::OpenGLRenderer()
		: m_WindowHandle(nullptr)
	{
		s_Shader = nullptr;
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
		m_TriangleVA = OpenGLVertexArray::Create();
		m_TriangleVA->Bind();

		{// Create shader
			AP_PROFILE_SCOPE("Create shader");
			s_Shader = Shader::Create("D:/Dev/C++/Apsis/Apsis/src/Assets/OpenGL/DefaultShader.glsl");
			s_Shader->Bind();
		}

		{// Create vertex buffer
			AP_PROFILE_SCOPE("Create vertex buffer");
			m_TriangleVA->AddVertexBuffer({
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			});
		}

		{// Create index buffer
			AP_PROFILE_SCOPE("Create index buffer");
			unsigned int indices[3] = { 0, 1, 2 };
			m_TriangleVA->AddIndexBuffer(indices, sizeof(indices));
		}


		return true;
	}

	void OpenGLRenderer::BeginDrawImpl()
	{
		AP_PROFILE_FN();
		std::vector<std::string> uniformsList = 
		{
			"u_Color"
		};

		for (auto& uniform : uniformsList)
		{
			int location = glGetUniformLocation(s_Shader->GetID(), uniform.c_str());
			if (location == -1)
			{
				AP_WARN_C("Uniform {0} not found", uniform);
				continue;
			}
			m_UniformLocations[uniform] = location;
		}
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

	void OpenGLRenderer::SetClearColorImpl(const Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
		m_ClearColor = col;
	}

	void OpenGLRenderer::OnResizeImpl()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::DrawCircleImpl(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::DrawRectImpl(const Eigen::Vector2i& position, float width, float height, const Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
		glBindVertexArray(m_TriangleVA->GetID());
		glUniform4f(m_UniformLocations["u_Color"], col.x(), col.y(), col.z(), col.w());
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}

}