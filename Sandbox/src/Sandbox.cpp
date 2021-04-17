#include "Sandbox.h"

#include <iostream>

#include "MainLayer.h"

Sandbox::Sandbox()
{
	EmlpaceLayer(new MainLayer());
}