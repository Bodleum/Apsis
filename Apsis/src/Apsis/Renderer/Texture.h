#pragma once
#include "Apsis/Core/Core.h"
	//#include <memory>
	//#include <chrono>

namespace A {

	class Texture
	{
	public:
		static Shared<Texture> Create(unsigned int width, unsigned int height, void* data, unsigned int size);
		static Shared<Texture> Create(unsigned int width, unsigned int height);
		static Shared<Texture> Create(const char* path);
		virtual ~Texture() = default;

		virtual void SetData(void* data, unsigned int size) = 0;
		virtual void Bind(unsigned int slot = 0) const = 0;

		virtual const int GetWidth() const = 0;
		virtual const int GetHeight() const = 0;
	};

}
