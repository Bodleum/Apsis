#include "apch.h"
#include "OpenGLBuffer.h"
#include "OpenGLHeaders.h"
#include "Apsis/Renderer/Renderer.h"

namespace A {

	OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& vertex_buffer)
	{
		AP_PROFILE_FN();

		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(float), &vertex_buffer[0], GL_STATIC_DRAW);

		m_Layout = Renderer::GetGraphicsResources()->DefaultShader->GetVertexBufferLayout();
		if (!ValidateLayout(vertex_buffer))
		{
			AP_CRIT_C("Invalid vertex buffer layout");
			return;
		}
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		AP_PROFILE_FN();
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		AP_PROFILE_FN();
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



	OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<unsigned int>& index_buffer)
	{
		AP_PROFILE_FN();

		m_IndexCount = index_buffer.size();
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof(unsigned int), &index_buffer[0], GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		AP_PROFILE_FN();
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		AP_PROFILE_FN();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

}