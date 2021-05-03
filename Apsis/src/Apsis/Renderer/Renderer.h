#pragma once
#include "Apsis/Core/Core.h"	// Shared
#include <Eigen/Core>

namespace A {

	class Window;

	class Renderer
	{
	public:
		virtual ~Renderer() = default;
		static Shared<Renderer> Create(Unique<Window>& window);

		static inline bool Init(Unique<Window>& window) { return s_Instance->InitImpl(window); }
		
		static inline void BeginDraw() { s_Instance->BeginDrawImpl(); }
		static inline void EndDraw() { s_Instance->EndDrawImpl(); }
		static inline void Clear() { s_Instance->ClearImpl(); }
		static inline void SetClearColor(const Eigen::Vector4f& col) { s_Instance->SetClearColorImpl(col); }
		static inline void OnResize() { s_Instance->OnResizeImpl(); }

		static inline void DrawCircle(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col) { s_Instance->DrawCircleImpl(position, radius, col); }
		static inline void DrawRect(const Eigen::Vector2i& position, float width, float height, const Eigen::Vector4f& col) { s_Instance->DrawRectImpl(position, width, height, col); }

		static inline RendererAPI GetAPI() { return SystemInfo::GetRendererAPI(); }
		static inline void SetAPI(RendererAPI api) { s_RendererAPI = api; }

	protected:
		virtual bool InitImpl(Unique<Window>& window) = 0;

		virtual void BeginDrawImpl() = 0;
		virtual void EndDrawImpl() = 0;
		virtual void ClearImpl() = 0;
		virtual void SetClearColorImpl(const Eigen::Vector4f& col) = 0;
		virtual void OnResizeImpl() = 0;

		virtual void DrawCircleImpl(const Eigen::Vector2i& position, float radius, const Eigen::Vector4f& col) = 0;
		virtual void DrawRectImpl(const Eigen::Vector2i& position, float width, float height, const Eigen::Vector4f& col) = 0;

		// ---   Vars   ---
		Eigen::Vector4f m_ClearColor = { 0.8f, 0.2f, 0.8f, 1.0f };

	private:
		static RendererAPI s_RendererAPI;
		static Shared<Renderer> s_Instance;
	};

}