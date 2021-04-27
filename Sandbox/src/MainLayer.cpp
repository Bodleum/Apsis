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

	A::Shader::Create(A::ShaderType::Vertex, "D:/Dev/C++/Apsis/Apsis/src/Assets/OpenGL/DefaultShader.glsl");
}

void MainLayer::OnRemove()
{
}

void MainLayer::OnUpdate(A::MicroSeconds time_step)
{
}

bool MainLayer::OnEvent(A::Shared<A::Event> evt)
{
	return false;
}

void MainLayer::OnRender()
{
	A::Renderer::DrawCircle(Eigen::Vector2i(100, 100), 100, Eigen::Vector4f(1.0f, 1.0f, 0.5f, 1.0f));
	//A::Renderer::DrawRect(Eigen::Vector2i(250, 250), 100, 150, Eigen::Vector4f(1.0f, 1.0f, 0.5f, 1.0f));
}
