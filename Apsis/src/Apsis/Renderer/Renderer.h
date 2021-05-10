#pragma once
#include "Apsis/Core/Core.h"	// Shared
#include "Apsis/Renderer/Shader.h"
#include "Apsis/Renderer/Texture.h"
#include "Apsis/Renderer/Cam.h"
//#include <Eigen/Core>		Included in Cam.h

namespace A {

	class Window;
	struct GraphicsResources
	{
		RendererAPI RendererAPI;
		Eigen::Vector4f ClearColor;
		Shared<Texture> DefaultTexture;
		Eigen::Vector4f DefaultColor;
		Shared<Shader> DefaultShader;

		GraphicsResources(A::RendererAPI renderer_api, const Eigen::Vector4f& clear_color, Shared<Texture> texture, const Eigen::Vector4f& color, Shared<Shader> shader)
			: RendererAPI(renderer_api), ClearColor(clear_color), DefaultTexture(texture), DefaultColor(color), DefaultShader(shader)
		{
		}

	};


	class Renderer
	{
	public:
		virtual ~Renderer() = default;
		static Shared<Renderer> Create(Unique<Window>& window);

		static inline bool Init(Unique<Window>& window) { return s_Instance->InitImpl(window); }
		
		static inline void BeginDraw(Shared<Cam> cam) { s_Instance->BeginDrawImpl(cam); }
		static inline void EndDraw() { s_Instance->EndDrawImpl(); }
		static inline void Clear() { s_Instance->ClearImpl(); }
		static inline void SetClearColor(const Eigen::Vector4f& col) { s_Instance->SetClearColorImpl(col); }
		static inline void OnResize() { s_Instance->OnResizeImpl(); }

		static inline void DrawCircle(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col) { s_Instance->DrawCircleImpl(position, radius, col); }
		static inline void DrawRect(const Eigen::Vector2i& position, float width, float height, Shared<Texture> texture, const Eigen::Vector4f& col = Eigen::Vector4f{1.0f, 1.0f, 1.0f, 1.0f}) { s_Instance->DrawRectImpl(position, width, height, texture,col); }

		static inline RendererAPI GetAPI() { return SystemInfo::GetRendererAPI(); }
		static inline void SetAPI(RendererAPI api) { s_GraphicsResources->RendererAPI = api; }
		static inline const Shared<GraphicsResources> GetGraphicsResources() { return s_GraphicsResources; }

	protected:
		virtual bool InitImpl(Unique<Window>& window) = 0;

		virtual void BeginDrawImpl(Shared<Cam> cam) = 0;
		virtual void EndDrawImpl() = 0;
		virtual void ClearImpl() = 0;
		virtual void SetClearColorImpl(const Eigen::Vector4f& col) = 0;
		virtual void OnResizeImpl() = 0;

		virtual void DrawCircleImpl(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col) = 0;
		virtual void DrawRectImpl(const Eigen::Vector2i& position, float width, float height, Shared<Texture> texture, const Eigen::Vector4f& col/*= {1.0f, 1.0f, 1.0f, 1.0f}*/) = 0;

		static Shared<GraphicsResources> s_GraphicsResources;
		static Shared<Cam> s_Cam;

	private:
		static Shared<Renderer> s_Instance;
	};

}