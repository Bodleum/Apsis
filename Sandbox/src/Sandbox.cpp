#include "Sandbox.h"

#include <iostream>

Sandbox::Sandbox()
{
	AP_TRACE("Hello world but logged!!");

	int x;
	std::cout << "x -> ";
	std::cin >> x;
	AP_ASSERT_C(x < 0, "x must be < 0!, x = {0}", x);
	AP_ASSERT_NOMSG(x < 0);

	system("pause");
}