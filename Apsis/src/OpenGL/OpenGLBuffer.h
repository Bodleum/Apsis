#pragma once
#include "Apsis/Renderer/Buffer.h"

namespace A {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const std::vector<float>& vertex_buffer);
		virtual ~OpenGLVertexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() override;
		virtual bool ValidateLayout(const std::vector<float>& vertex_buffer) override;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{

	};

}
