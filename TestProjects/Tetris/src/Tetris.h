#pragma once
#include "Apsis.h"

class Tetris : public A::App
{
public:
	Tetris(A::AppArgs args);
	virtual ~Tetris() = default;
};

A::App* A::CreateApp(AppArgs args) { return new Tetris(args); }