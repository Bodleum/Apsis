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
		void Bind();

		void AddVertexBuffer(const std::vector<float>& vertex_buffer);
		void AddIndexBuffer(unsigned int* index_buffer, unsigned int size);

	private:
		unsigned int m_VertexArrayID = 0;
		Unique<VertexBuffer> m_VertexBuffer = nullptr;
		unsigned int m_IndexBufferID = 0;
	};

}