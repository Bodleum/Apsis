#pragma once
#include "apch.h"
#include "Apsis/Core/Platform.h"

namespace A { struct AppArgs {}; }

#ifdef AP_PLATFORM_WIN
	int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nShowCmd);

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

		struct WinAppArgs : public AppArgs
		{
			HINSTANCE hInstance;
			HINSTANCE hPrevInstance;
			LPWSTR pCmdLine;
			int nShowCmd;
		};
	}
#else
	int main(int argc, char** argv);
#endif // AP_PLATFORM_WIN
