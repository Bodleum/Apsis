#include "apch.h"
#include "VertexArray.h"
	//#include "Apsis/Renderer/Buffer.h"

#include "Headers.h"
	//#include <glad/glad.h>
	//#include <GLFW/glfw3.h>
#include "OpenGL/Shader.h"
	//#include "Apsis/Renderer/Shader.h"
	//	#include "Apsis/Core/Core.h"
	//		#include <memory>
	//		#include <chrono>

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

	void OpenGLVertexArray::AddVertexBuffer(const std::vector<float>& vertex_buffer)
	{
		AP_PROFILE_FN();
		
		if (m_VertexBuffer)
		{
			AP_CRIT_C("A vertex buffer already exists");
			return;
		}

		glBindVertexArray(m_VertexArrayID);
		m_VertexBuffer = VertexBuffer::Create(vertex_buffer);
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

	void OpenGLVertexArray::AddIndexBuffer(const std::vector<unsigned int>& index_buffer)
	{
		AP_PROFILE_FN();

		if (m_IndexBuffer)
		{
			AP_CRIT_C("An index buffer already exists");
			return;
		}

		glBindVertexArray(m_VertexArrayID);
		m_IndexBuffer = IndexBuffer::Create(index_buffer);
		m_IndexBuffer->Bind();
	}

}