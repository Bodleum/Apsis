#include "apch.h"
#include "OpenGLRenderer.h"
	//#include "Apsis/Core/Window.h"
	//#include "Apsis/Renderer/Renderer.h"
	//	#include "Apsis/Core/SystemInfo.h"
	//	#include "Apsis/Renderer/Cam.h"
	//		#include <Eigen/Core>
	//		#include <Eigen/Geometry>
	//		#include <Eigen/Dense>
	//	#include "Apsis/Renderer/Shader.h"
	//		#include "Apsis/Core/Core.h"
	//			#include <memory>
	//			#include <chrono>
	//	#include "Apsis/Renderer/Texture.h"
	//		#include "Apsis/Core/Core.h"
	//			#include <memory>
	//			#include <chrono>

#include "OpenGLHeaders.h"
	//#include <glad/glad.h>
	//#include <GLFW/glfw3.h>

#include "OpenGL/OpenGLVertexArray.h"
	//#include "Apsis/Renderer/Buffer.h"

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
			unsigned int whiteTextureData = 0xffffffff;
			s_GraphicsResources->DefaultTexture = Texture::Create(1, 1, &whiteTextureData, sizeof(whiteTextureData));
		}

		{// Get uniform locations
			AP_PROFILE_SCOPE("Get uniform locations");
			std::vector<const char*> uniformsList =
			{
				"u_MVP",
				"u_Color",
				"u_Texture"
			};

			for (auto& uniform : uniformsList)
			{
				int location = glGetUniformLocation(s_GraphicsResources->DefaultShader->GetID(), uniform);
				if (location == -1)
				{
					AP_WARN_C("Uniform {0} not found", uniform);
					continue;
				}
				m_UniformLocations[uniform] = location;
			}
		}

		return true;
	}

	void OpenGLRenderer::BeginDrawImpl(Shared<Cam> cam)
	{
		AP_PROFILE_FN();
		s_Cam = cam;
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

	void OpenGLRenderer::DrawRectImpl(const Eigen::Vector2i& position, float width, float height, float angle, Shared<Texture> texture, const Eigen::Vector4f& col/*= {1.0f, 1.0f, 1.0f, 1.0f}*/)
	{
		AP_PROFILE_FN();
		glBindVertexArray(m_RectVA->GetID());
		
		Eigen::Affine3f modelTransform = Eigen::Affine3f::Identity();
		modelTransform = modelTransform * s_Cam->GetVP();
		modelTransform.translate(Eigen::Vector3f((float)position.x(), (float)position.y(), 1.0f));
		modelTransform.rotate(Eigen::Quaternionf(Eigen::AngleAxisf(angle * 3.1415f / 180.0f, Eigen::Vector3f::UnitZ())));
		modelTransform.scale(Eigen::Vector3f(width, height, 1.0f));

		if (texture)
			texture->Bind();
		else
			s_GraphicsResources->DefaultTexture->Bind();

		glUniformMatrix4fv(m_UniformLocations["u_MVP"], 1, GL_FALSE, modelTransform.matrix().data());
		glUniform4f(m_UniformLocations["u_Color"], col.x(), col.y(), col.z(), col.w());
		glUniform1i(m_UniformLocations["u_Texture"], 0);
		glDrawElements(GL_TRIANGLES, m_RectVA->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
	}

}