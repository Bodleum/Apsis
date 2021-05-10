#pragma once
#include "apch.h"

namespace A {

	class VertexBufferLayout;

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
		None = 0,
		Bool,
		Int,
		UnsignedInt,
		Float,
		Double
	};

	inline const unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		AP_PROFILE_FN();
		static std::unordered_map<ShaderDataType, unsigned int> sizeMap =
		{
			{ShaderDataType::None, 0},
			{ShaderDataType::Bool, 1},
			{ShaderDataType::Int, 4},
			{ShaderDataType::UnsignedInt, 4},
			{ShaderDataType::Float, 4},
			{ShaderDataType::Double, 8}
		};

		if (type == ShaderDataType::None)
			AP_CRIT_C("Unknown shader data type");

		return sizeMap[type];
	}
	
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
		VertexBufferLayout(const std::vector<BufferElement>& elements)
			: m_Elements(elements), m_Stride(0)
		{
			AP_PROFILE_FN();
			unsigned int offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};

}