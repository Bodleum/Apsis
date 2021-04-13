#pragma once
#include "Apsis/Core/Platform.h"
#include "Apsis/Core/Core.h"

#pragma warning(push, 0)
	#include <stdio.h>
	#include <fcntl.h>
	#include <io.h>
	#include <fstream>
	#include <iostream>
	#include <string>
	#include <sstream>
	#include <array>
	#include <vector>

	#ifdef AP_PLATFORM_WIN
		#include <Windows.h>
	#endif
#pragma warning(pop)

#include "Apsis/Core/Logger.h"
#include "Apsis/Utility/Instrumentor.h"