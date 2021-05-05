#pragma once
#include "Apsis/Renderer/Shader.h"

namespace A {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		// Inherited via Shader
		virtual void Bind() override;

	private:
		// Inheruted via Shader
		virtual const std::unordered_map<ShaderType, std::string> Read(const std::string& path) override;
		virtual void CompileAndLink(std::unordered_map<ShaderType, std::string> shader_sources) override;
		virtual Shared<VertexBufferLayout> DetectVertexBufferLayout(const std::string& vertex_shader_source) override;


		const ShaderDataType GLSLTypeToShaderDataType(const std::string& type) const;
	};

	const unsigned int ShaderDataTypeToOpenGLType(ShaderDataType type);
}