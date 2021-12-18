#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace Grout {
	class GROUT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core LOG macros
#define GRT_CORE_TRACE(...)    ::Grout::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GRT_CORE_INFO(...)     ::Grout::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GRT_CORE_WARN(...)     ::Grout::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GRT_CORE_ERROR(...)    ::Grout::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GRT_CORE_CRITICAL(...) ::Grout::Log::GetCoreLogger()->critical(__VA_ARGS__)
							   
// Client LOG macros
#define GRT_TRACE(...)         ::Grout::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GRT_INFO(...)          ::Grout::Log::GetClientLogger()->info(__VA_ARGS__)
#define GRT_WARN(...)          ::Grout::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GRT_ERROR(...)         ::Grout::Log::GetClientLogger()->error(__VA_ARGS__)
#define GRT_CRITICAL(...)      ::Grout::Log::GetClientLogger()->critical(__VA_ARGS__)