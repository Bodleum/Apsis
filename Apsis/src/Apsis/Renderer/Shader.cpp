#include "apch.h"
#include "Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace A {

	Shared<Shader> Shader::Create(ShaderType type, const std::string& path)
	{
		AP_PROFILE_FN();

		switch (SystemInfo::GetRendererAPI())
		{
		case RendererAPI::OpenGL:	return MakeShared<OpenGLShader>(type, path);
		default:		break;
		}
		AP_ERROR_C("Unknown renderer API, could not create shader");
		return nullptr;
	}

}