#pragma once
#include "Apsis.h"

class MainLayer : public A::Layer
{
public:
	MainLayer();
	virtual ~MainLayer() = default;

	// Inherited via Layer
	virtual void OnAdd() override;
	virtual void OnRemove() override;
	virtual void OnUpdate(A::MicroSeconds time_step) override;
	virtual bool OnEvent(A::Event& evt) override;

	bool testfn(A::MouseButtonDownEvent& evt);
};