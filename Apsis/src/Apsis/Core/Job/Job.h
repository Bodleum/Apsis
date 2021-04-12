#pragma once
#include <functional>

namespace A {

	template<typename ...Args>
	using JobFunction = std::function<void(Args... args)>;

	/*
	* TODO: Add counter
	*/

	template<typename ...Args>
	struct Job
	{
		JobFunction<Args... args> JobFn;
		// Counter* Counter;
	};
}