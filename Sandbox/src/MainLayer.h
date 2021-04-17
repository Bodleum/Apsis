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
	virtual void OnUpdate() override;
	virtual bool OnEvent(A::Event& evt) override;
};