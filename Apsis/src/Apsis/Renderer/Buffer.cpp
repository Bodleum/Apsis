#include "apch.h"
#include "Buffer.h"
#include "Apsis/Core/SystemInfo.h"
#include "OpenGL/OpenGLBuffer.h"

namespace A {

	Unique<VertexBuffer> VertexBuffer::Create(const std::vector<float>& vertex_buffer)
	{
		switch (SystemInfo::GetRendererAPI())
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLVertexBuffer>(vertex_buffer);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}

}
