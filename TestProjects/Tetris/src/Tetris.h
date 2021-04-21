#pragma once
#include "Apsis.h"

class Tetris : public A::App
{
public:
	Tetris();
	virtual ~Tetris() = default;
};

AP_CREATE_APP(Tetris);