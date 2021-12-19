#pragma once

#ifdef GRT_PLATAFORM_WINDOWS
	#ifdef GRT_BUILD_DLL
		#define GROUT_API __declspec(dllexport)
	#else
		#define GROUT_API __declspec(dllimport)
	#endif
#else
	#error Grout only supports Windows
#endif

#define BIT(x) (1 << x)

