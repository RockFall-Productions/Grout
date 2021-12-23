#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Grout {
	class GROUT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return core_logger_; }
		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return client_logger_; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger_;
		static std::shared_ptr<spdlog::logger> client_logger_;
	};
}

// Core LOG macros
#define GRT_CORE_TRACE(...)    ::Grout::Log::get_core_logger()->trace(__VA_ARGS__)
#define GRT_CORE_INFO(...)     ::Grout::Log::get_core_logger()->info(__VA_ARGS__)
#define GRT_CORE_WARN(...)     ::Grout::Log::get_core_logger()->warn(__VA_ARGS__)
#define GRT_CORE_ERROR(...)    ::Grout::Log::get_core_logger()->error(__VA_ARGS__)
#define GRT_CORE_CRITICAL(...) ::Grout::Log::get_core_logger()->critical(__VA_ARGS__)
							   
// Client LOG macros
#define GRT_TRACE(...)         ::Grout::Log::get_client_logger()->trace(__VA_ARGS__)
#define GRT_INFO(...)          ::Grout::Log::get_client_logger()->info(__VA_ARGS__)
#define GRT_WARN(...)          ::Grout::Log::get_client_logger()->warn(__VA_ARGS__)
#define GRT_ERROR(...)         ::Grout::Log::get_client_logger()->error(__VA_ARGS__)
#define GRT_CRITICAL(...)      ::Grout::Log::get_client_logger()->critical(__VA_ARGS__)