#pragma once
//#include "Apsis/Core/Job/Job.h"	Included in Queue.h
#include "Apsis/Core/Job/Queue.h"

namespace A {

	class JobSystem
	{
	public:
		static JobSystem* Get();

		Queue* HighPriorityQueue;
		Queue* NormalPriorityQueue;
		Queue* LowPriorityQueue;

	private:
		JobSystem();

		static JobSystem* s_Instance;
	};

}