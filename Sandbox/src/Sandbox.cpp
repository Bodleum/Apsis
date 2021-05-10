#include "Sandbox.h"

#include <iostream>

#include "MainLayer.h"

Sandbox::Sandbox()
{
	CreateCam(A::CamType::Ortho);
	EmlpaceLayer(new MainLayer());
}