#include "apch.h"
#include "Main.h"

#include "Apsis/Core/App.h"
//#include "Apsis/Core/Logger.h"	Included in pch
#include "Apsis/Core/Input/Input.h"

extern A::App* A::CreateApp();

#ifdef AP_PLATFORM_WIN


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd)
{

	// Fix io to console
	if (A::CreateNewConsole(1024))
	{
		#define AP_CONSOLE_IO_TESTS 0
		// Tests
		#if AP_CONSOLE_IO_TESTS
			int i;

			// test stdio
			fprintf(stdout, "Test output to stdout\n");
			fprintf(stderr, "Test output to stderr\n");
			fprintf(stdout, "Enter an integer to test stdin: ");
			if (scanf("%d", &i))
				printf("You entered %d\n", i);

			// test iostreams
			std::cout << "Test output to std::cout" << std::endl;
			std::cerr << "Test output to std::cerr" << std::endl;
			std::clog << "Test output to std::clog" << std::endl;
			std::cout << "Enter an integer to test std::cin: ";
			std::cin >> i;
			std::cout << "You entered " << i << std::endl;

			std::cout << "------------------\n" << "End of testing" << std::endl;
			system("pause");
			system("cls");
		#endif
	}


	AP_PROFILE_BEGIN_SESSION("Startup", "Apsis - Startup.json");
		A::Logger::Init();
		{
			A::AppArgs args;
			args.MainFnArgs.hInstance = hInstance;
			args.MainFnArgs.hPrevInstance = hPrevInstance;
			args.MainFnArgs.pCmdLine = pCmdLine;
			args.MainFnArgs.nShowCmd = nShowCmd;
			A::App::SetAppArgs(args);
		}
		A::App* app = A::CreateApp();
	AP_PROFILE_END_SESSION();

	AP_PROFILE_BEGIN_SESSION("Runtime", "Apsis - Runtime.json");
		app->Run();
	AP_PROFILE_END_SESSION();

	AP_PROFILE_BEGIN_SESSION("Shutdown", "Apsis - Shutdown.json");
		delete app;
		A::ReleaseConsole();
	AP_PROFILE_END_SESSION();

	return 0;
}

namespace A {

	bool RedirectConsoleIO()
	{
		bool result = true;
		FILE* fp;

		// Redirect STDIN if the console has an input handle
		if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
				result = false;
			else
				setvbuf(stdin, NULL, _IONBF, 0);

		// Redirect STDOUT if the console has an output handle
		if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
				result = false;
			else
				setvbuf(stdout, NULL, _IONBF, 0);

		// Redirect STDERR if the console has an error handle
		if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
			if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
				result = false;
			else
				setvbuf(stderr, NULL, _IONBF, 0);

		// Make C++ standard streams point to console as well.
		std::ios::sync_with_stdio(true);

		// Clear the error state for each of the C++ standard streams.
		std::wcout.clear();
		std::cout.clear();
		std::wcerr.clear();
		std::cerr.clear();
		std::wcin.clear();
		std::cin.clear();

		return result;
	}

	bool ReleaseConsole()
	{
		bool result = true;
		FILE* fp;

		// Just to be safe, redirect standard IO to NUL before releasing.

		// Redirect STDIN to NUL
		if (freopen_s(&fp, "NUL:", "r", stdin) != 0)
			result = false;
		else
			setvbuf(stdin, NULL, _IONBF, 0);

		// Redirect STDOUT to NUL
		if (freopen_s(&fp, "NUL:", "w", stdout) != 0)
			result = false;
		else
			setvbuf(stdout, NULL, _IONBF, 0);

		// Redirect STDERR to NUL
		if (freopen_s(&fp, "NUL:", "w", stderr) != 0)
			result = false;
		else
			setvbuf(stderr, NULL, _IONBF, 0);

		// Detach from console
		if (!FreeConsole())
			result = false;

		return result;
	}

	void AdjustConsoleBuffer(int16_t minLength)
	{
		// Set the screen buffer to be big enough to scroll some text
		CONSOLE_SCREEN_BUFFER_INFO conInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &conInfo);
		if (conInfo.dwSize.Y < minLength)
			conInfo.dwSize.Y = minLength;
		SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), conInfo.dwSize);
	}

	bool CreateNewConsole(int16_t minLength)
	{
		bool result = false;

		// Release any current console and redirect IO to NUL
		ReleaseConsole();

		// Attempt to create new console
		if (AllocConsole())
		{
			AdjustConsoleBuffer(minLength);
			result = RedirectConsoleIO();
		}

		return result;
	}

	bool AttachParentConsole(int16_t minLength)
	{
		bool result = false;

		// Release any current console and redirect IO to NUL
		ReleaseConsole();

		// Attempt to attach to parent process's console
		if (AttachConsole(ATTACH_PARENT_PROCESS))
		{
			AdjustConsoleBuffer(minLength);
			result = RedirectConsoleIO();
		}

		return result;
	}

}

#else

int main(int argc, char** argv)
{
	AP_PROFILE_BEGIN_SESSION("Startup", "Apsis - Startup.json");
		A::Logger::Init();
		A::App::LogInfo();
		A::App* app = A::CreateApp();
	AP_PROFILE_END_SESSION();

	AP_PROFILE_BEGIN_SESSION("Runtime", "Apsis - Runtime.json");
		app->Run();
	AP_PROFILE_END_SESSION();

	AP_PROFILE_BEGIN_SESSION("Shutdown", "Apsis - Shutdown.json");
		delete app;
	AP_PROFILE_END_SESSION();

	return 0;
}

#endif // AP_PLATFORM_WIN