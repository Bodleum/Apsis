#include "Sandbox.h"

#include <iostream>

Sandbox::Sandbox()
{
	AP_TRACE("Hello world but logged!!");
	if (A::Platform::Windows)
		AP_INFO("Platform: Windows");


}