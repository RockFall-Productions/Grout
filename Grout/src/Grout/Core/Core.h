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

// Used in the event system to make it possible
// for filtering multiple categories on an enum
#define BIT(i) (1 << i)

// Wraps a function to be passed as a parameter - currently used for the callbacks
#define GRT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#include <memory>
namespace Grout {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}

#include "Grout/Core/Log.h"
#include "Grout/Core/Assert.h"