#include "apch.h"
#include "JobSystem.h"

namespace A {

	void SubmitJob(JobFunction job_fn)//, void* params)
	{
		SubmitJob({ job_fn, nullptr });
	}

	void SubmitJob(Job job)
	{
		job.JobFn(job.Params);
	}

}