#pragma once
#include "Apsis/Core/Core.h"
	//#include <memory>
	//#include <chrono>

namespace A {

	class VertexBufferLayout;

	typedef enum class ShaderType : unsigned short
	{
		Unknown		= 0,
		Vertex		= 1,
		Pixel		= 2,
		Fragment	= 2
	};

	ShaderType StringToShaderType(const std::string& string);
	std::string ShaderTypeToString(ShaderType shader_type);

	class Shader
	{
	public:
		virtual ~Shader() = default;
		static Shared<Shader> Create(const char* path);
		static Shared<Shader> CreateFromString(const char* shader_source);

		virtual void Bind() = 0;
		virtual inline const unsigned int GetID() const { return m_ShaderProgramID; }
		virtual inline const Shared<VertexBufferLayout> GetVertexBufferLayout() const { return m_VertexBufferLayout; }

	protected:
		virtual Shared<VertexBufferLayout> DetectVertexBufferLayout(const std::string& vertex_shader_source) = 0;

		unsigned int m_ShaderProgramID;
		Shared<VertexBufferLayout> m_VertexBufferLayout;

	private:
		static char* Read(const char* path);
	};

	typedef enum class ShaderDataType : unsigned short
	{
		Unknown = 0,
		Bool,
		Int,
		UnsignedInt,
		Float,
		Double
	};

	unsigned int ShaderDataTypeSize(ShaderDataType type);
	
	struct BufferElement
	{
		ShaderDataType Type;
		unsigned int Count;
		std::string Name;
		bool Normalized;
		unsigned int Size;
		unsigned int Offset;

		BufferElement(ShaderDataType type, unsigned int count, const std::string& name, bool normalized = false)
			: Type(type), Count(count), Name(name), Normalized(normalized), Size(ShaderDataTypeSize(type) * count), Offset(0)
		{
		}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout(const std::vector<BufferElement>& elements);

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};

}