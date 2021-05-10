#pragma once
#include "Apsis/Renderer/Shader.h"

namespace A {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* shader_source);
		virtual ~OpenGLShader();

		// Inherited via Shader
		virtual void Bind() override;

	private:
		const std::unordered_map<ShaderType, std::string> Process(const char* shader_source);
		void CompileAndLink(std::unordered_map<ShaderType, std::string> shader_sources);
		// Inheruted via Shader
		virtual Shared<VertexBufferLayout> DetectVertexBufferLayout(const std::string& vertex_shader_source) override;


		const ShaderDataType GLSLTypeToShaderDataType(const std::string& type) const;
	};

	const unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type);
}