#ifndef PLATFORMDEFINITIONS_H
#define PLATFORMDEFINITIONS_H

#ifdef _WIN32

#ifndef NOMINMAX
#define NOMINMAX
#endif // !NOMINMAX


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <SDKDDKVer.h>
#include <windows.h>
#include <tchar.h>


#endif // _WIN32

namespace SaltnPepperEngine
{
	namespace Platform
	{
#ifdef _WIN32

#ifdef SNP_PLATFORM_WINDOWS
		using PlatformWindow = HWND;
#endif
		

#endif //_WIN32

		inline void Quit()
		{
#ifdef _WIN32

#ifdef SNP_PLATFORM_WINDOWS
			PostQuitMessage(0);
#endif


#endif //_WIN32
		}


		struct WindowProperties
		{
			int Width = 0;
			int Height = 0;
			float Dpi = 72.0f;
			float AspectRatio = 0.0f;
		};


		inline void GetWindowProperties(PlatformWindow window, WindowProperties* properties)
		{
#ifdef SNP_PLATFORM_WINDOWS
			properties->Dpi = static_cast<float>(GetDpiForWindow(window));
#endif // SNP_PLATFORM_WINDOWS


#ifdef SNP_PLATFORM_WINDOWS

			RECT winRect;
			GetClientRect(window, &winRect);
			properties->Width = static_cast<int>(winRect.right = winRect.left);
			properties->Height = static_cast<int>(winRect.bottom = winRect.top);
			properties->AspectRatio = static_cast<float>(properties->Width / properties->Height);
#endif


		}
	}
}




#endif // !PLATFORMDEFINITIONS_H
