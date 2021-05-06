#pragma once
#include "Apsis/Core/Core.h"	// Shared
#include <string>

namespace A {

	class Texture
	{
	public:
		Shared<Texture> Create(const std::string& path);
		virtual ~Texture() = default;

		virtual void Bind(unsigned int slot = 0) const = 0;

		virtual const int GetWidth() const = 0;
		virtual const int GetHeight() const = 0;
	};

}
