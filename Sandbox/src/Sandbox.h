#pragma once
#include "Apsis.h"

class Sandbox : public A::Application
{
public:
	Sandbox();
	virtual ~Sandbox() = default;

private:

};

A::Application* A::CreateApplication() { return new Sandbox; }