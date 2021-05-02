#pragma once
#include "apch.h"

namespace A {

	typedef enum class ShaderType : unsigned short
	{
		None		= 0,
		Vertex		= 1,
		Pixel		= 2,
		Fragment	= 2
	};

	inline std::unordered_map<std::string, ShaderType> StringToShaderType =
	{
		{"ShaderType::Vertex",		ShaderType::Vertex},
		{"ShaderType::Pixel",		ShaderType::Pixel},
		{"ShaderType::Fragment",	ShaderType::Fragment}
	};

	inline std::unordered_map<ShaderType, std::string> ShaderTypeToString =
	{
		{ShaderType::Vertex,	"Vertex"},
		{ShaderType::Pixel,		"Pixel"},
		{ShaderType::Fragment,	"Fragment"}
	};

	class Shader
	{
	public:
		virtual ~Shader() = default;
		static Shared<Shader> Create(const std::string& path);

		virtual void Bind() = 0;
		virtual inline const unsigned int GetID() const { return m_ShaderProgramID; }

	protected:
		virtual const std::unordered_map<ShaderType, std::string> Read(const std::string& path) = 0;
		virtual void CompileAndLink(std::unordered_map<ShaderType, std::string> shader_sources) = 0;

		unsigned int m_ShaderProgramID;
	};

}