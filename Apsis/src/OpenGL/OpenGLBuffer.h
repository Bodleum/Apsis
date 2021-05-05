#pragma once
#include "Apsis/Renderer/Buffer.h"

namespace A {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertex_buffer, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() override;
		virtual bool ValidateLayout(float* vertex_buffer, unsigned int size) override;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{

	};

}
