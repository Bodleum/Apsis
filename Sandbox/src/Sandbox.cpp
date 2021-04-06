#include "Sandbox.h"

#include <iostream>

Sandbox::Sandbox()
{
	std::cout << "Hello world!\n";
	if (A::Platform::Windows)
		std::cout << "Platform: Windows\n";

}