#include "MainLayer.h"

MainLayer::MainLayer()
	: Layer()
{

}

void MainLayer::OnAdd()
{
	m_Enabled = true;

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
	m_Enabled = false;
}

void MainLayer::OnUpdate()
{
}

bool MainLayer::OnEvent(A::Event& evt)
{
	return false;
}
