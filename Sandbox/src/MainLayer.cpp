#include "MainLayer.h"

MainLayer::MainLayer()
	: Layer()
{

}

void MainLayer::OnAdd()
{
	// Logging tests
	#define LOGGING_TESTS 0
	{
		#if LOGGING_TESTS
		AP_TRACE("Hello world but logged!!");

		int x;
		std::cout << "x -> ";
		std::cin >> x;
		AP_ASSERT_C(x < 0, "x must be < 0!, x = {0}", x);
		AP_ASSERT_NOMSG(x < 0);

		system("pause");
		#endif // LOGGING_TESTS
	}

}

void MainLayer::OnRemove()
{
}

void MainLayer::OnUpdate(A::MicroSeconds time_step)
{
	m_ColorHSV.x() += time_step.count() * 0.000000005;
	if (m_ColorHSV.x() > 1.0f)
		m_ColorHSV.x() -= 1.0f;

	m_ColorRGB = A::HSVToRGB(m_ColorHSV);
}

bool MainLayer::OnEvent(A::Shared<A::Event> evt)
{
	return false;
}

bool MainLayer::testfn(A::MouseButtonDownEvent& evt)
{
	return false;
}

void MainLayer::OnRender()
{
	//A::Renderer::DrawCircle(Eigen::Vector2i(100, 100), 100, Eigen::Vector4f(1.0f, 1.0f, 0.5f, 1.0f));
	A::Renderer::DrawRect(Eigen::Vector2i(250, 250), 100, 150, m_ColorRGB);
}
