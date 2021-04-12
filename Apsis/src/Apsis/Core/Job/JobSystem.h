#pragma once
//#include "Apsis/Core/Job/Job.h"	Included in Queue.h
#include "Apsis/Core/Job/Queue.h"

namespace A {

	//void SubmitJob(JobFunction job_fn, void* params);
	void SubmitJob(JobFunction job_fn);
	void SubmitJob(Job job);

}