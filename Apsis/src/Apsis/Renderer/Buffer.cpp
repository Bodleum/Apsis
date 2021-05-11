#include "apch.h"
#include "Buffer.h"
#include "Apsis/Core/SystemInfo.h"
#include "OpenGL/OpenGLBuffer.h"

namespace A {

	Unique<VertexBuffer> VertexBuffer::Create(const std::vector<float>& vertex_buffer)
	{
		AP_PROFILE_FN();
		switch (SystemInfo::RendererAPI)
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLVertexBuffer>(vertex_buffer);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}

	Unique<IndexBuffer> IndexBuffer::Create(const std::vector<unsigned int>& index_buffer)
	{
		AP_PROFILE_FN();
		switch (SystemInfo::RendererAPI)
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLIndexBuffer>(index_buffer);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}

}
