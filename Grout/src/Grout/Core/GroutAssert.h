#pragma once

#include "Grout/Core/Log.h"

#ifdef GRT_ENABLE_ASSERTS
	#define GRT_ASSERT(x, ...) {if (!(x)) { GRT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GRT_CORE_ASSERT(x, ...) {if (!(x)) { GRT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GRT_ASSERT(x, ...)
	#define GRT_CORE_ASSERT(x, ...)
#endif