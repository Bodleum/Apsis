#pragma once
#include "Apsis/Core/Window.h"
#include "Apsis/Renderer/Renderer.h"
#include "OpenGL/OpenGLShader.h"


struct GLFWwindow;

namespace A {


	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();


		// Inherited via Renderer
		virtual bool InitImpl(Unique<Window>& window) override;
		virtual void ClearImpl() override;
		virtual void SetClearColorImpl(Eigen::Vector4f& col) override;
		virtual void OnResizeImpl() override;

		virtual void DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) override;
		virtual void DrawRectImpl(Eigen::Vector2i& position, float width, float height, Eigen::Vector4f& col) override;

		virtual void BeginDrawImpl() override;
		virtual void EndDrawImpl() override;

	private:
		GLFWwindow* m_WindowHandle;
		unsigned int m_VertexArrayID = 0;
		unsigned int m_VertexBufferID = 0;
		unsigned int m_IndexBufferID = 0;
		Shared<Shader> m_Shader;
	};

}