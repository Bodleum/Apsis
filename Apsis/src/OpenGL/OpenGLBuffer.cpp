#include "apch.h"
#include "OpenGLBuffer.h"
#include "OpenGLHeaders.h"
#include "Apsis/Renderer/Renderer.h"

namespace A {

	OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& vertex_buffer)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(float), &vertex_buffer[0], GL_STATIC_DRAW);

		m_Layout = Renderer::GetShader()->GetVertexBufferLayout();
		if (!ValidateLayout(vertex_buffer))
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

	bool OpenGLVertexBuffer::ValidateLayout(const std::vector<float>& vertex_buffer)
	{
		AP_PROFILE_FN();

		// Check total size
		unsigned int stride = m_Layout->GetStride();
		if (vertex_buffer.size() * sizeof(float) % stride != 0)
			return false;

		return true;
	}

}