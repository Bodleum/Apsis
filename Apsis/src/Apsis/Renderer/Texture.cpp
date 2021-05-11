#include "apch.h"
#include "Texture.h"
#include "Apsis/Core/SystemInfo.h"
#include "OpenGL/OpenGLTexture.h"

namespace A {

	Shared<Texture> Texture::Create(unsigned int width, unsigned int height)
	{
		AP_PROFILE_FN();
		switch (SystemInfo::RendererAPI)
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLTexture>(width, height);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}

	Shared<Texture> Texture::Create(const std::string& path)
	{
		AP_PROFILE_FN();
		switch (SystemInfo::RendererAPI)
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLTexture>(path);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}
}
