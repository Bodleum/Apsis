#include "apch.h"
#include "OpenGLShader.h"
#include "OpenGLHeaders.h"

#include <fstream>

namespace A {

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		AP_PROFILE_FN();

		auto shaderSources = Read(path);
		CompileAndLink(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderProgramID);
	}

	const std::unordered_map<ShaderType, std::string> OpenGLShader::Read(const std::string& path)
	{
		AP_PROFILE_FN();

		std::unordered_map<ShaderType, std::string> mapOfShaderSources{};


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
		std::string fileData;
		fileData.resize(length);
		ifs.read(&fileData[0], length);	// Read into fileData
		ifs.close();

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
			ShaderType shaderType = StringToShaderType[shaderTypeString];
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

				AP_ERROR_C("{0} shader failed to compile:\n{1}", ShaderTypeToString[type], infoLog.data());

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
			for (auto [type, shader] : compiledShaders)
				glDeleteShader(shader);

			AP_ERROR_C("Shader failed to link:\n{1}", infoLog.data());

			return;
		}

		// Always detach shaders after a successful link.
		for (auto [type, shader] : compiledShaders)
		{
			glDetachShader(program, shader);
			glDeleteShader(shader);
		}

		m_ShaderProgramID = program;
	}
}