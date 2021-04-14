#include "Sandbox.h"

#include <iostream>

#include "MainLayer.h"

Sandbox::Sandbox(A::AppArgs args)
	: A::App(args)
{
	EmlpaceLayer(new MainLayer());
}