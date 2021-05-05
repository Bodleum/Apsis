#pragma once
#include "Apsis/Renderer/Shader.h"

namespace A {

	class VertexBuffer
	{
	public:
		static Unique<VertexBuffer> Create(float* vertex_buffer, unsigned int size);
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual const unsigned int GetID() const { return m_ID; }
		virtual const Shared<VertexBufferLayout>& GetLayout() const { return m_Layout; }
		virtual bool ValidateLayout(float* vertex_buffer, unsigned int size) = 0;

	protected:
		unsigned int m_ID = 0;
		float* m_Buffer = nullptr;
		Shared<VertexBufferLayout> m_Layout = nullptr;
	};

	class IndexBuffer
	{

	};

}
