#pragma once
#include "Apsis.h"

class Sandbox : public A::App
{
public:
	Sandbox(A::AppArgs* args);
	virtual ~Sandbox() = default;
};

A::App* A::CreateApp(AppArgs* args) { return new Sandbox; }