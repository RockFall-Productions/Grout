#pragma once

// Here we define how the macros for classes works
// i.e. for Windows it should export or import DLL's
#ifdef GRT_PLATAFORM_WINDOWS
	#ifdef GRT_BUILD_DLL
		#define GROUT_API __declspec(dllexport)
	#else
		#define GROUT_API __declspec(dllimport)
	#endif
#else
	#error Grout only supports Windows
#endif

// Used in the event system to make it possible
// for filtering multiple categories on an enum
#define BIT(x) (1 << x)

