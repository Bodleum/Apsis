#pragma once

namespace A {

	using JobEntryPoint = void* (void* params);

	enum class Priority
	{
		Low, Normal, High
	};

	/*
	* TODO: Add counter
	*/

	struct Job
	{
		JobEntryPoint* EntryPoint;
		void* Params;
		Priority Priority;
		// Counter* Counter;
	};
}