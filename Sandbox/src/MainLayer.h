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

private:
	Eigen::Vector4f m_ColorHSV = { 0.0f, 1.0f, 1.0f, 1.0f };
	Eigen::Vector4f m_ColorRGB = { 1.0f, 0.0f, 0.0f, 1.0f };
	A::Shared<A::Texture> m_CamelTexture = nullptr;
};