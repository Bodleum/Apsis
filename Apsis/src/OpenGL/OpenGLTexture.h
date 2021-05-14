#pragma once
#include "Apsis/Renderer/Texture.h"

namespace A {

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(unsigned int width, unsigned int height, void* data, unsigned int size);
		OpenGLTexture(unsigned int width, unsigned int height);
		OpenGLTexture(const char* path);
		virtual ~OpenGLTexture();

		// Inherited via Texture
		virtual void SetData(void* data, unsigned int size);
		virtual void Bind(unsigned int slot = 0) const override;
		virtual inline const int GetWidth() const override { return m_Width; }
		virtual inline const int GetHeight() const override { return m_Height; }

	protected:
		unsigned int m_TextureID = 0;
		const char* m_FilePath = nullptr;
		void* m_LocalBuffer = nullptr;
		int m_Width, m_Height, m_BBP = 0;
	};

}
