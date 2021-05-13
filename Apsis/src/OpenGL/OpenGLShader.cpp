#include "apch.h"
#include "OpenGLShader.h"
#include "OpenGLHeaders.h"

#include <fstream>

namespace A {

	OpenGLShader::OpenGLShader(const char* shader_source)
	{
		AP_PROFILE_FN();

		auto shaderSources = Process(shader_source);
		CompileAndLink(shaderSources);
		m_VertexBufferLayout = DetectVertexBufferLayout(shaderSources[ShaderType::Vertex]);
	}

	OpenGLShader::~OpenGLShader()
	{
		AP_PROFILE_FN();
		glDeleteProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Bind()
	{
		AP_PROFILE_FN();
		glUseProgram(m_ShaderProgramID);
	}
	
	const std::unordered_map<ShaderType, std::string> OpenGLShader::Process(const char* shader_source)
	{
		AP_PROFILE_FN();

		std::unordered_map<ShaderType, std::string> mapOfShaderSources{};
		std::string fileData = shader_source;
		
		// Find shader type
		size_t shaderTypePos = fileData.find("ShaderType::", 0);
		if (shaderTypePos == std::string::npos)
		{
			AP_ERROR_C("No shaders found");
			return {};
		}

		while (shaderTypePos != std::string::npos)
		{
			size_t lineEnd = fileData.find_first_of("\n\r", shaderTypePos);
			std::string shaderTypeString = fileData.substr(shaderTypePos, lineEnd - shaderTypePos);
			ShaderType shaderType = StringToShaderType(shaderTypeString);
			size_t shaderTypeLength = strlen(shaderTypeString.c_str());
			size_t shaderBeginPos = lineEnd + 1;

			// Find next shader start
			size_t nextShaderStart = fileData.find("ShaderType::", shaderBeginPos);

			// Test for duplicate types
			if (mapOfShaderSources.count(shaderType) != 0)
			{
				AP_WARN_C("Multiple shaders of {0} found, first will be used", shaderTypeString);
			}
			else
			{
				std::string shaderSource = nextShaderStart == std::string::npos ? fileData.substr(shaderBeginPos) : fileData.substr(shaderBeginPos, nextShaderStart - shaderBeginPos);

				// Remove extra new lines
				size_t shaderSourceTextStart = shaderSource.find_first_not_of("\r\n\0", 0);
				if (shaderSourceTextStart == std::string::npos)
					shaderSourceTextStart = 0;
				size_t shaderSourceTextEnd = shaderSource.find_last_not_of("\r\n\0", strlen(shaderSource.c_str()));
				if (shaderSourceTextEnd == std::string::npos)
					shaderSourceTextEnd = shaderSource.size();
				shaderSource = shaderSource.substr(shaderSourceTextStart, 1 + shaderSourceTextEnd - shaderSourceTextStart);

				mapOfShaderSources[shaderType] = shaderSource;
			}

			shaderTypePos = nextShaderStart;
		}

		// Test for required shaders
		if (mapOfShaderSources.count(ShaderType::Vertex) == 0)
			AP_ERROR_C("No Vertex shader found, one must be provided");
		if (mapOfShaderSources.count(ShaderType::Pixel) == 0)
			AP_ERROR_C("No Pixel shader found, one must be provided");

		return mapOfShaderSources;
	}

	void OpenGLShader::CompileAndLink(std::unordered_map<ShaderType, std::string> shader_sources)
	{
		AP_PROFILE_FN();

		// Get a program object.
		GLuint program = glCreateProgram();

		std::unordered_map<ShaderType, unsigned int> compiledShaders{};
		GLuint OpenGLShaderType = 0;
		for (auto& [type, shaderSrc] : shader_sources)
		{
			// Create an empty shader handle of correct type
			switch (type)
			{
				case A::ShaderType::Vertex:		OpenGLShaderType = GL_VERTEX_SHADER;	break;
				case A::ShaderType::Fragment:	OpenGLShaderType = GL_FRAGMENT_SHADER;	break;
				default: AP_ERROR_C("Unknown shader type {0}", type); return;
			}
			GLuint shader = glCreateShader(OpenGLShaderType);

			// Send the shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = shaderSrc.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				AP_ERROR_C("{0} shader failed to compile:\n{1}", ShaderTypeToString(type), infoLog.data());

				return;
			}

			compiledShaders[type] = shader;

			// Shader has been successfully compiled.
			// Attach our shader to our m_RendererID
			glAttachShader(program, shader);
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto& [type, shader] : compiledShaders)
				glDeleteShader(shader);

			AP_ERROR_C("Shader failed to link:\n{1}", infoLog.data());

			return;
		}

		// Always detach shaders after a successful link.
		for (auto& [type, shader] : compiledShaders)
		{
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}

		m_ShaderProgramID = program;
	}

	Shared<VertexBufferLayout> OpenGLShader::DetectVertexBufferLayout(const std::string& vertex_shader_source)
	{
		AP_PROFILE_FN();
		size_t pos, eol;
		pos = vertex_shader_source.find(" in ");
		std::string line;
		std::vector<BufferElement> elements{};

		while (pos != std::string::npos)
		{
			pos++; // + 1 for space at start
			eol = vertex_shader_source.find_first_of(";", pos);
			line = vertex_shader_source.substr(pos, eol - pos);
			size_t linePos = 0;

			linePos = line.find_first_not_of(" \t\n\r\f\v", linePos + 2); // + 2 for length of "in"
			size_t typeEndPos = line.find(" ", linePos);
			std::string typeString = line.substr(linePos, typeEndPos - linePos);
			ShaderDataType type = GLSLTypeToShaderDataType(typeString);

			// Get count
			unsigned int count;
			{
				linePos = line.find_first_of("1234567890", linePos);
				size_t countEndPos = line.find_last_of("1234567890", typeEndPos);
				std::stringstream ss(line.substr(linePos, countEndPos - linePos + 1));
				ss >> count;
			}

			// Get name
			linePos = line.find_first_not_of(" \t\n\r\f\v", typeEndPos);
			std::string name = line.substr(linePos, eol - linePos);

			elements.push_back({ type, count, name });
			pos = vertex_shader_source.find(" in ", eol);
		}

		return MakeShared<VertexBufferLayout>(elements);
	}

	const ShaderDataType OpenGLShader::GLSLTypeToShaderDataType(const std::string& type) const
	{
		AP_PROFILE_FN();
		// Clip off numbers
		size_t typeStringEnd = type.find_last_not_of("1234567890");
		std::string newType = type.substr(0, typeStringEnd + 1);

		static std::unordered_map<std::string, ShaderDataType> typeMap =
		{
			{"bool", ShaderDataType::Bool},
			{"int", ShaderDataType::Int},
			{"uint", ShaderDataType::UnsignedInt},
			{"float", ShaderDataType::Float},
			{"double", ShaderDataType::Double},

			{"bvec", ShaderDataType::Bool},
			{"ivec", ShaderDataType::Int},
			{"uvec", ShaderDataType::UnsignedInt},
			{"vec", ShaderDataType::Float},
			{"dvec", ShaderDataType::Double},

			{"mat", ShaderDataType::Float},
			{"dmat", ShaderDataType::Double}
		};

		return typeMap[newType];
	}



	const unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		AP_PROFILE_FN();
		static std::unordered_map<ShaderDataType, GLenum> typeMap =
		{
			{ShaderDataType::Bool, GL_BOOL},
			{ShaderDataType::Int, GL_INT},
			{ShaderDataType::UnsignedInt, GL_UNSIGNED_INT},
			{ShaderDataType::Float, GL_FLOAT},
			{ShaderDataType::Double, GL_DOUBLE}
		};

		return typeMap[type];
	}
}