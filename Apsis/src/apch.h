#pragma once
#include "Apsis/Core/Core.h"
	//#include <memory>
	//#include <chrono>

#pragma warning(push, 0)
	#include <algorithm>
	#include <array>
	#include <fcntl.h>
	#include <fstream>
	#include <io.h>
	#include <iostream>
	#include <map>
	#include <sstream>
	#include <stdio.h>
	#include <string>
	#include <unordered_map>
	#include <vector>


	#ifdef AP_PLATFORM_WIN
		#define NOMINMAX
		#include <Windows.h>
	#endif
#pragma warning(pop)

#include "Apsis/Core/Logger.h"
#include "Apsis/Utility/Instrumentor.h"
	//#include <fstream>
	//#include <mutex>
#include "Apsis/Core/SystemInfo.h"