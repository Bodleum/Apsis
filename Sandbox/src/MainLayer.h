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
	virtual void OnRender() override;
	virtual bool OnEvent(A::Shared<A::Event> evt) override;

	bool testfn(A::MouseButtonDownEvent& evt);
	bool testfn2(A::TestEvent& evt);
};