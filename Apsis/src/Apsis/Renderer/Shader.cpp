#include "apch.h"
#include "Shader.h"

#include "OpenGL/OpenGLShader.h"

namespace A {

	Shared<Shader> Shader::Create(const char* path)
	{
		AP_PROFILE_FN();

		switch (SystemInfo::RendererAPI)
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

		switch (SystemInfo::RendererAPI)
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


	ShaderType StringToShaderType(const std::string& string)
	{
		AP_PROFILE_FN();

		static std::unordered_map<std::string, ShaderType> stringMap =
		{
			{"ShaderType::Vertex",		ShaderType::Vertex},
			{"ShaderType::Pixel",		ShaderType::Pixel},
			{"ShaderType::Fragment",	ShaderType::Fragment}
		};

		try
		{
			return stringMap.at(string);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("Unknown shader type {0}", string);
			return ShaderType::Unknown;
		}
	}

	std::string ShaderTypeToString(ShaderType shader_type)
	{
		static std::unordered_map<ShaderType, std::string> shaderTypeMap =
		{
			{ShaderType::Vertex,	"Vertex"},
			{ShaderType::Pixel,		"Pixel"},
			{ShaderType::Fragment,	"Fragment"}
		};

		try
		{
			return shaderTypeMap.at(shader_type);
		}
		catch (const std::out_of_range& e)
		{
			AP_WARN_C("Unknown shader type {0}", (unsigned short)shader_type);
			return "Unknown";
		}
	}

	unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		AP_PROFILE_FN();
		static std::unordered_map<ShaderDataType, unsigned int> sizeMap =
		{
			{ShaderDataType::Bool, 1},
			{ShaderDataType::Int, 4},
			{ShaderDataType::UnsignedInt, 4},
			{ShaderDataType::Float, 4},
			{ShaderDataType::Double, 8}
		};


		try
		{
			return sizeMap.at(type);
		}
		catch (const std::out_of_range& e)
		{
			AP_CRIT_C("Unknown shader data type {0}", (unsigned short)type);
			return 0;
		}
	}

}