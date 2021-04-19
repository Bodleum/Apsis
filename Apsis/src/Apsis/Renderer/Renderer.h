#pragma once
#include "apch.h"	// Shared
#include <Eigen/Core>

namespace A {

	class Renderer
	{
	public:
		virtual ~Renderer() = default;

		virtual bool Init(void* window_handle) = 0;
		
		virtual void Clear() = 0;
		virtual void SetClearColor(Eigen::Vector4f& col) = 0;

		virtual void DrawCircle(Eigen::Vector2i& position, float radius, Eigen::Vector4f& col) = 0;

		static Shared<Renderer> Create();

	protected:
		Eigen::Vector4f m_ClearColor = { 0.8f, 0.2f, 0.8f, 1.0f };
	};

}