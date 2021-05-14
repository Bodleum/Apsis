#pragma once

#ifdef AP_PLATFORM_WIN
	struct HINSTASCE;
	int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, wchar_t* pCmdLine, int nShowCmd);

	namespace A {
		/*
		* Console fixes
		* https://stackoverflow.com/questions/191842/how-do-i-get-console-output-in-c-with-a-windows-program
		*/
		bool RedirectConsoleIO();
		bool ReleaseConsole();
		void AdjustConsoleBuffer(int16_t minLength);
		bool CreateNewConsole(int16_t minLength);
		bool AttachParentConsole(int16_t minLength);

		struct MainFnArgs
		{
			MainFnArgs()
				: hInstance(nullptr), hPrevInstance(nullptr), pCmdLine(nullptr), nShowCmd(0)
			{
			}

			HINSTANCE hInstance;
			HINSTANCE hPrevInstance;
			wchar_t* pCmdLine;
			int nShowCmd;
		};

		struct AppArgs
		{
			AppArgs()
				: MainFnArgs()
			{
			}

			MainFnArgs MainFnArgs;
		};
	}
#else
	int main(int argc, char** argv);

	namespace A {

		struct WindowArgs {};
		struct AppArgs {};

	}
#endif // AP_PLATFORM_WIN
