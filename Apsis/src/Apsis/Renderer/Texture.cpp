#include "apch.h"
#include "Texture.h"
#include "Apsis/Core/SystemInfo.h"
#include "OpenGL/OpenGLTexture.h"

namespace A {

	Shared<Texture> Texture::Create(const std::string& path)
	{
		AP_PROFILE_FN();
		switch (SystemInfo::GetRendererAPI())
		{
			case RendererAPI::OpenGL: return MakeUnique<OpenGLTexture>(path);
		}
		AP_CRIT_C("Unknown renderer API");
		return nullptr;
	}
}
