#include "apch.h"
#include "OpenGLTexture.h"
#include "OpenGLHeaders.h"

#include <stb_image.h>

namespace A {

	OpenGLTexture::OpenGLTexture(const std::string& path)
		: m_TextureID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BBP(0)
	{
		AP_PROFILE_FN();

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		{// Load image
			stbi_set_flip_vertically_on_load(1);
			m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BBP, 4);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const void*)m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Free image data after passing to GPU
		// Could be moved to destructor if a copy is to be retained
		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLTexture::Bind(unsigned int slot = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

}
