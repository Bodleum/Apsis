#pragma once
#include "Apsis/Renderer/Renderer.h"
#include "Apsis/Core/Window.h"

namespace A {

	using OpenGLContext = HGLRC;

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();

		void CreateContext(OpenGLContext* context, Unique<Window>& window, bool make_current);

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
		OpenGLContext m_Context;
	};

}