#include "apch.h"
#include "OpenGLRenderer.h"
#include "OpenGLHeaders.h"

namespace A {

	OpenGLRenderer::OpenGLRenderer()
		: m_WindowHandle(nullptr)
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

		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_WindowHandle = (GLFWwindow*)window->GetHandle();
		m_RectVA = OpenGLVertexArray::Create();
		m_RectVA->Bind();

		{// Create default shader
			AP_PROFILE_SCOPE("Create default shader");

			const char* shaderSource =
#include "Assets/OpenGL/DefaultShader.shader"
				;
			 
			s_GraphicsResources->DefaultShader = Shader::CreateFromString(shaderSource);
			s_GraphicsResources->DefaultShader->Bind();
		}

		{// Create rect vertex array
			AP_PROFILE_SCOPE("Create rect vertex array");
			m_RectVA->AddVertexBuffer({
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			});
			m_RectVA->AddIndexBuffer({ 0, 1, 2, 0, 2, 3 });
		}

		{// Create default texture
			AP_PROFILE_SCOPE("Create default texture");
			s_GraphicsResources->DefaultTexture = Texture::Create(1, 1);
			unsigned int whiteTextureData = 0xffffffff;
			s_GraphicsResources->DefaultTexture->SetData((void*)(&whiteTextureData), sizeof(whiteTextureData));
		}

		return true;
	}

	void OpenGLRenderer::BeginDrawImpl(Shared<Cam> cam)
	{
		AP_PROFILE_FN();
		std::vector<std::string> uniformsList = 
		{
			"u_Proj",
			"u_Color",
			"u_Texture"
		};

		for (auto& uniform : uniformsList)
		{
			int location = glGetUniformLocation(s_GraphicsResources->DefaultShader->GetID(), uniform.c_str());
			if (location == -1)
			{
				AP_WARN_C("Uniform {0} not found", uniform);
				continue;
			}
			m_UniformLocations[uniform] = location;
		}

		glUniformMatrix4fv(m_UniformLocations["u_Proj"], 1, GL_FALSE, cam->GetProj().data());
	}

	void OpenGLRenderer::EndDrawImpl()
	{
		AP_PROFILE_FN();
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLRenderer::ClearImpl()
	{
		AP_PROFILE_FN();
		glClearColor(s_GraphicsResources->ClearColor.x(), s_GraphicsResources->ClearColor.y(), s_GraphicsResources->ClearColor.z(), s_GraphicsResources->ClearColor.w());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::SetClearColorImpl(const Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
		s_GraphicsResources->ClearColor = col;
	}

	void OpenGLRenderer::OnResizeImpl()
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::DrawCircleImpl(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col)
	{
		AP_PROFILE_FN();
	}

	void OpenGLRenderer::DrawRectImpl(const Eigen::Vector2i& position, float width, float height, Shared<Texture> texture, const Eigen::Vector4f& col/*= {1.0f, 1.0f, 1.0f, 1.0f}*/)
	{
		AP_PROFILE_FN();
		glBindVertexArray(m_RectVA->GetID());

		if (texture)
			texture->Bind();
		else
			s_GraphicsResources->DefaultTexture->Bind();

		glUniform4f(m_UniformLocations["u_Color"], col.x(), col.y(), col.z(), col.w());
		glUniform1i(m_UniformLocations["u_Texture"], 0);
		glDrawElements(GL_TRIANGLES, m_RectVA->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

}