#pragma once
#include "Apsis.h"


class Sandbox : public A::App
{
public:
	Sandbox();
	virtual ~Sandbox() = default;
};

AP_CREATE_APP(Sandbox);