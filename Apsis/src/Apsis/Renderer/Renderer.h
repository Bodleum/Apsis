#pragma once
#include "apch.h"	// Shared
#include <Eigen/Core>

namespace A {

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		static inline bool Init(void* window_handle) { return s_Instance->InitImpl(window_handle); }
		
		static inline void BeginDraw() { s_Instance->BeginDrawImpl(); }
		static inline void EndDraw() { s_Instance->EndDrawImpl(); }
		static inline void Clear() { s_Instance->ClearImpl(); }
		static inline void SetClearColor(Eigen::Vector4f& col) { s_Instance->SetClearColorImpl(col); }
		static inline void OnResize() { s_Instance->OnResizeImpl(); }

		static inline void DrawCircle(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) { s_Instance->DrawCircleImpl(position, radius, col); }

		static Shared<Renderer> Create();

	protected:
		virtual bool InitImpl(void* window_handle) = 0;

		virtual void BeginDrawImpl() = 0;
		virtual void EndDrawImpl() = 0;
		virtual void ClearImpl() = 0;
		virtual void SetClearColorImpl(Eigen::Vector4f& col) = 0;
		virtual void OnResizeImpl() = 0;

		virtual void DrawCircleImpl(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) = 0;

		// ---   Vars   ---
		Eigen::Vector4f m_ClearColor = { 0.8f, 0.2f, 0.8f, 1.0f };

	private:
		static Shared<Renderer> s_Instance;
	};

}