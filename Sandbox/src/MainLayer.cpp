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
}

bool MainLayer::OnEvent(A::Shared<A::Event> evt)
{
	AP_INFO(*evt);
	A::LocalDispatcher ld(evt);
	ld.Dispatch<A::MouseButtonDownEvent>(BIND_EVT_FN(MainLayer::testfn));
	ld.Dispatch<A::TestEvent>(BIND_EVT_FN(MainLayer::testfn2));

	return false;
}

bool MainLayer::testfn(A::MouseButtonDownEvent& evt)
{
	AP_INFO("Test! {0}", evt);
	A::EventDispatcher::SendEvent(A::MakeShared<A::TestEvent>("Delay!"), 2s);
	//std::chrono::seconds{ 2 }
	return false;
}

bool MainLayer::testfn2(A::TestEvent& evt)
{
	AP_INFO(evt);
	return false;
}

void MainLayer::OnRender()
{
	A::Renderer::DrawCircle(Eigen::Vector2i(100, 100), 100, Eigen::Vector4f(1.0f, 1.0f, 0.5f, 1.0f));
	A::Renderer::DrawRect(Eigen::Vector2i(250, 250), 100, 150, Eigen::Vector4f(1.0f, 1.0f, 0.5f, 1.0f));
}
