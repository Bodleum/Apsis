#pragma once
#include "Apsis/Renderer/Buffer.h"

namespace A {

	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		inline static Unique<OpenGLVertexArray> Create() { return MakeUnique<OpenGLVertexArray>(); }

		inline const unsigned int GetID() const { return m_VertexArrayID; }
		inline const unsigned int GetIndexCount() const { return m_IndexBuffer->GetIndexCount(); }
		void Bind();

		void AddVertexBuffer(const std::vector<float>& vertex_buffer);
		void AddIndexBuffer(const std::vector<unsigned int>& index_buffer);

	private:
		unsigned int m_VertexArrayID = 0;
		Unique<VertexBuffer> m_VertexBuffer = nullptr;
		Unique<IndexBuffer> m_IndexBuffer = nullptr;
	};

}