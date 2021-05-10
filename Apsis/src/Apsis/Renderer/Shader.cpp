#include "apch.h"
#include "Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace A {

	Shared<Shader> Shader::Create(const char* path)
	{
		AP_PROFILE_FN();

		switch (SystemInfo::GetRendererAPI())
		{
		case RendererAPI::OpenGL:	return MakeShared<OpenGLShader>(Read(path));
		default:		break;
		}
		AP_ERROR_C("Unknown renderer API, could not create shader");
		return nullptr;
	}

	Shared<Shader> Shader::CreateFromString(const char* shader_source)
	{
		AP_PROFILE_FN();

		switch (SystemInfo::GetRendererAPI())
		{
		case RendererAPI::OpenGL:	return MakeShared<OpenGLShader>(shader_source);
		default:		break;
		}
		AP_ERROR_C("Unknown renderer API, could not create shader");
		return nullptr;
	}

	char* Shader::Read(const char* path)
	{
		AP_PROFILE_FN();

		std::ifstream ifs(path, std::ios::in);
		if (!ifs)
		{
			AP_CRIT_C("Could not open shader file {0}", path);
			return {};
		}

		// Read file
		ifs.seekg(0, ifs.end);
		int length = ifs.tellg();	// Get size of file
		ifs.seekg(0, ifs.beg);
		if (length == -1)
		{
			AP_ERROR_C("Could not read shader file {0}", path);
			return {};
		}
		char* fileData = (char*)malloc(length);
		ifs.read(fileData, length);	// Read into fileData
		ifs.close();

		return fileData;
	}


}