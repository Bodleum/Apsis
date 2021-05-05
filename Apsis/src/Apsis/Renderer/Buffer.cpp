#include "apch.h"
#include "Buffer.h"
#include "Apsis/Core/SystemInfo.h"
#include "OpenGL/OpenGLBuffer.h"

namespace A {

	Unique<VertexBuffer> VertexBuffer::Create(float* vertex_buffer, unsigned int size)
	{
		switch (SystemInfo::GetRendererAPI())
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLVertexBuffer>(vertex_buffer, size);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}

}
