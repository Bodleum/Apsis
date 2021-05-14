#pragma once
#include "Apsis/Core/Window.h"
#include "Apsis/Renderer/Renderer.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLVertexArray.h"

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
		virtual void SetClearColorImpl(const Eigen::Vector4f& col) override;
		virtual void OnResizeImpl() override;

		virtual void DrawCircleImpl(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col) override;
		virtual void DrawRectImpl(const Eigen::Vector2i& position, float width, float height, float angle, Shared<Texture> texture, const Eigen::Vector4f& col/*= {1.0f, 1.0f, 1.0f, 1.0f}*/) override;

		virtual void BeginDrawImpl(Shared<Cam> cam) override;
		virtual void EndDrawImpl() override;

	private:
		GLFWwindow* m_WindowHandle = nullptr;
		Unique<OpenGLVertexArray> m_RectVA = nullptr;
		std::unordered_map<const char*, int> m_UniformLocations = {};
	};

}