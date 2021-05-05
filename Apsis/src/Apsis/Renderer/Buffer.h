#pragma once
#include "Apsis/Renderer/Shader.h"

namespace A {

	class VertexBuffer
	{
	public:
		static Unique<VertexBuffer> Create(const std::vector<float>& vertex_buffer);
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual const unsigned int GetID() const { return m_ID; }
		virtual const Shared<VertexBufferLayout>& GetLayout() const { return m_Layout; }
		virtual bool ValidateLayout(const std::vector<float>& vertex_buffer) = 0;

	protected:
		unsigned int m_ID = 0;
		Shared<VertexBufferLayout> m_Layout = nullptr;
	};

	class IndexBuffer
	{
	public:
		static Unique<IndexBuffer> Create(const std::vector<unsigned int>& index_buffer);
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual const unsigned int GetID() const { return m_ID; }

	protected:
		unsigned int m_ID = 0;
	};

}
