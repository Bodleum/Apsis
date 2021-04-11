#include "apch.h"
#include "JobSystem.h"

namespace A {

	//JobSystem::s_Instance = nullptr;

	JobSystem* A::JobSystem::Get()
	{
		if (!s_Instance)
			s_Instance = new JobSystem;
		return s_Instance;
	}

}