#pragma once
#include "Apsis/Renderer/Shader.h"

namespace A {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(ShaderType type, const std::string& path);
		virtual ~OpenGLShader();

		virtual void Bind() override;
	};

}