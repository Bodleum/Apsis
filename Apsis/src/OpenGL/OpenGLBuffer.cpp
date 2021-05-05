#include "apch.h"
#include "OpenGLBuffer.h"
#include "OpenGLHeaders.h"
#include "Apsis/Renderer/Renderer.h"

namespace A {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertex_buffer, unsigned int size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertex_buffer, GL_STATIC_DRAW);

		m_Layout = Renderer::GetShader()->GetVertexBufferLayout();
		if (!ValidateLayout(vertex_buffer, size))
		{
			AP_CRIT_C("Invalid vertex buffer layout");
			return;
		}
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	bool OpenGLVertexBuffer::ValidateLayout(float* vertex_buffer, unsigned int size)
	{
		AP_PROFILE_FN();

		// Check total size
		unsigned int stride = m_Layout->GetStride();
		if (size % stride != 0)
			return false;

		return true;
	}

}