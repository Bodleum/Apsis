#pragma once
#include <queue>

#include "Apsis/Core/Job/Job.h"

namespace A {

	class Queue
	{
	public:
		inline void Add(Job job) { m_JobQueue.push(job); }

	private:
		std::queue<Job> m_JobQueue;
	};

}
