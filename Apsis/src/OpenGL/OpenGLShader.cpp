#include "apch.h"
#include "OpenGLShader.h"
#include "OpenGLHeaders.h"

#include <fstream>

namespace A {

	OpenGLShader::OpenGLShader(ShaderType type, const std::string& path)
	{
		AP_PROFILE_FN();

		m_Type = type;
		std::string shaderTypeString = "ShaderType::" + ShaderTypeToString[type];
		size_t shaderTypeLength = strlen(shaderTypeString.c_str());

		std::ifstream ifs(path, std::ios::in);
		if (!ifs)
		{
			AP_CRIT_C("Could not open shader file {0}", path);
			return;
		}


		// Read file
		ifs.seekg(0, ifs.end);
		int length = ifs.tellg();	// Get size of file
		ifs.seekg(0, ifs.beg);
		if (length == -1)
		{
			AP_ERROR_C("Could not read shader file {0}", path);
			return;
		}
		std::string fileData;
		fileData.resize(length);
		ifs.read(&fileData[0], length);	// Read into fileData
		ifs.close();

		// Find shader type
		size_t shaderTypePos = fileData.find(shaderTypeString, 0);
		if (shaderTypePos == std::string::npos)
		{
			AP_ERROR_C("No shader of type {0} found", ShaderTypeToString[type]);
			return;
		}
		size_t shaderBeginPos = shaderTypePos + shaderTypeLength;

		// Test for duplicate types
		if (fileData.find(shaderTypeString, shaderBeginPos) != std::string::npos)
			AP_WARN_C("Multiple shaders of type {0} found, first will be used", ShaderTypeToString[type]);

		// Find next shader start
		size_t nextShaderStart = fileData.find("ShaderType::", shaderBeginPos);

		std::string shaderSource = nextShaderStart == std::string::npos ? fileData.substr(shaderBeginPos) : fileData.substr(shaderBeginPos, nextShaderStart - shaderBeginPos);

		// Remove extra new lines
		size_t shaderSourceTextStart = shaderSource.find_first_not_of("\r\n\0", 0);
		size_t shaderSourceTextEnd = shaderSource.find_last_not_of("\r\n\0", strlen(shaderSource.c_str()));
		shaderSource = shaderSource.substr(shaderSourceTextStart, shaderSourceTextEnd - shaderSourceTextStart);

		// ---   Compile   ---
		// Get a program object.
		GLuint program = glCreateProgram();

		// Create an empty shader handle of correct type
		GLuint OpenGLShaderType = 0;
		switch (type)
		{
			case A::ShaderType::Vertex:		OpenGLShaderType = GL_VERTEX_SHADER;	break;
			case A::ShaderType::Fragment:	OpenGLShaderType = GL_FRAGMENT_SHADER;	break;
			default: AP_ERROR_C("Unknown shader type {0}", type); return;
		}
		GLuint shader = glCreateShader(OpenGLShaderType);

		// Send the shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* sourceCStr = shaderSource.c_str();
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

		// Shader has been successfully compiled.
		// Attach our shader to our m_RendererID
		glAttachShader(program, shader);

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
			glDeleteShader(shader);

			AP_ERROR_C("{0} shader failed to link:\n\t{1}", ShaderTypeToString[type], infoLog.data());

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, shader);
		glDeleteShader(shader);

		m_ShaderID = program;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_ShaderID);
	}
}