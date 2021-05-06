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

		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_WindowHandle = (GLFWwindow*)window->GetHandle();
		m_RectVA = OpenGLVertexArray::Create();
		m_RectVA->Bind();

		{// Create shader
			AP_PROFILE_SCOPE("Create shader");
			s_Shader = Shader::Create("D:/Dev/C++/Apsis/Apsis/src/Assets/OpenGL/DefaultShader.glsl");
			s_Shader->Bind();
		}

		{// Create vertex buffer
			AP_PROFILE_SCOPE("Create vertex buffer");
			m_RectVA->AddVertexBuffer({
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			});
		}

		{// Create index buffer
			AP_PROFILE_SCOPE("Create index buffer");
			m_RectVA->AddIndexBuffer({ 0, 1, 2, 0, 2, 3 });
		}



		// Texture test
		m_Texture = Texture::Create("D:/Dev/C++/Apsis/Sandbox/res/camel_picture.png");
		m_Texture->Bind(0);


		return true;
	}

	void OpenGLRenderer::BeginDrawImpl()
	{
		AP_PROFILE_FN();
		std::vector<std::string> uniformsList = 
		{
			"u_Color",
			"u_Texture"
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
		glBindVertexArray(m_RectVA->GetID());
		//glUniform4f(m_UniformLocations["u_Color"], col.x(), col.y(), col.z(), col.w());
		glUniform1i(m_UniformLocations["u_Texture"], 0);
		glDrawElements(GL_TRIANGLES, m_RectVA->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

}