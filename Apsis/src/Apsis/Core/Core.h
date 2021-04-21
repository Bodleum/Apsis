#pragma once
#include <memory>
#include <chrono>

// Creating App
#define AP_CREATE_APP(appname) A::App* A::CreateApp() { return new appname(); }

// Unicode
#ifndef UNICODE
	#define UNICODE
#endif

// Bits
#define BIT_AT(x) (1 << x)

// Time
using namespace std::literals;
using namespace std::chrono_literals;
using namespace std::literals::chrono_literals;

// ---   Smart Pointers   ---
namespace A {

	// Unique
	template<typename T>
	using Unique = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Unique<T> MakeUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	// Shared
	template<typename T>
	using Shared = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Shared<T> MakeShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}