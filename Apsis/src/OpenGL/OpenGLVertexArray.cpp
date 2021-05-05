#include "apch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLHeaders.h"
#include "OpenGL/OpenGLShader.h"

namespace A {

	OpenGLVertexArray::OpenGLVertexArray()
	{
		AP_PROFILE_FN();
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		AP_PROFILE_FN();
	}

	void OpenGLVertexArray::Bind()
	{
		AP_PROFILE_FN();
		glBindVertexArray(m_VertexArrayID);
	}

	void OpenGLVertexArray::AddVertexBuffer(float* vertex_buffer, unsigned int size)
	{
		AP_PROFILE_FN();
		
		if (m_VertexBuffer)
		{
			AP_CRIT_C("A vertex buffer already exists");
			return;
		}

		glBindVertexArray(m_VertexArrayID);
		m_VertexBuffer = VertexBuffer::Create(vertex_buffer, size);
		m_VertexBuffer->Bind();

		// Set layout
		auto& elements = m_VertexBuffer->GetLayout()->GetElements();
		for (unsigned int index = 0; index < elements.size(); index++)
		{
			const auto& element = elements[index];
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.Count, ShaderDataTypeToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, m_VertexBuffer->GetLayout()->GetStride(), (const void*)element.Offset);
		}
	}

	void OpenGLVertexArray::AddIndexBuffer(unsigned int* index_buffer, unsigned int size)
	{
		AP_PROFILE_FN();

		if (m_IndexBufferID != 0)
		{
			AP_CRIT_C("An index buffer already exists");
			return;
		}

		glBindVertexArray(m_VertexArrayID);

		glCreateBuffers(1, &m_IndexBufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, index_buffer, GL_STATIC_DRAW);
	}

}