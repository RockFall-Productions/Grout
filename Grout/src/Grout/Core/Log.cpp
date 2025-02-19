#include "grtpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Grout {

	std::shared_ptr<spdlog::logger> Log::core_logger_;
	std::shared_ptr<spdlog::logger> Log::client_logger_;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");

		core_logger_ = spdlog::stdout_color_mt("Grout");
		core_logger_->set_level(spdlog::level::trace);

		client_logger_ = spdlog::stdout_color_mt("APP");
		client_logger_->set_level(spdlog::level::trace);

			// Adicionar sink para arquivo
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("grout.log", true);
		file_sink->set_level(spdlog::level::trace);

		// Logger combinado com terminal e arquivo
		core_logger_->sinks().push_back(file_sink);
		client_logger_->sinks().push_back(file_sink);
	}
}