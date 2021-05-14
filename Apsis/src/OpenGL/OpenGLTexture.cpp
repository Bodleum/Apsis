#include "apch.h"
#include "OpenGLTexture.h"
#include "OpenGLHeaders.h"

#include <stb_image.h>

namespace A {

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, void* data, unsigned int size)
		: m_LocalBuffer(data), m_Width(width), m_Height(height)
	{
		AP_PROFILE_FN();

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height)
	{
		AP_PROFILE_FN();

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	OpenGLTexture::OpenGLTexture(const char* path)
		: m_FilePath(path)
	{
		AP_PROFILE_FN();

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		{// Load image
			stbi_set_flip_vertically_on_load(1);
			m_LocalBuffer = (void*)stbi_load(path, &m_Width, &m_Height, &m_BBP, 4);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Free image data after passing to GPU
		// Could be moved to destructor if a copy is to be retained
		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		AP_PROFILE_FN();
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture::SetData(void* data, unsigned int size)
	{
		AP_PROFILE_FN();
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::Bind(unsigned int slot/*= 0*/) const
	{
		AP_PROFILE_FN();
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

}
