#include "apch.h"
#include "OpenGLShader.h"

#include <fstream>

namespace A {

	A::OpenGLShader::OpenGLShader(ShaderType type, const std::string& path)
	{
		AP_PROFILE_FN();

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
	}

}