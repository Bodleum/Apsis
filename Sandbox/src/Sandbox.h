#pragma once
#include "Apsis.h"

class Sandbox : public A::App
{
public:
	Sandbox();
	virtual ~Sandbox() = default;

private:

};

A::App* A::CreateApp() { return new Sandbox; }