#pragma once

// Here we define how the macros for classes works
// i.e. for Windows it should export or import DLL's
#ifdef GRT_PLATAFORM_WINDOWS
#else
	#error Grout only supports Windows
#endif

#ifdef GRT_DEBUG
	#define GRT_ENABLE_ASSERTS
#endif

#ifdef GRT_ENABLE_ASSERTS
	#define GRT_ASSERT(x, ...) {if (!(x)) { GRT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GRT_CORE_ASSERT(x, ...) {if (!(x)) { GRT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GRT_ASSERT(x, ...)
	#define GRT_CORE_ASSERT(x, ...)
#endif

// Used in the event system to make it possible
// for filtering multiple categories on an enum
#define BIT(i) (1 << i)

// Wraps a function to be passed as a parameter - currently used for the callbacks
#define GRT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)