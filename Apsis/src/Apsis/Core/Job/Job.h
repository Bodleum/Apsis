#pragma once

namespace A {

	using JobEntryPoint = void* (void* params);

	/*
	* TODO: Add counter
	*/

	struct Job
	{
		JobEntryPoint* EntryPoint;
		void* Params;
		// Counter* Counter;
	};
}