#include "Log.hpp"
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace SaltnPepperEngine
{
	namespace Debug
	{
#if	SNP_ENABLE_LOGGING

		std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
		std::vector<spdlog::sink_ptr> sinks;
#endif

		void Log::OnInit()
		{

#if SNP_ENABLE_LOGGING
			sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

#ifdef LOG_TO_FILE
			auto logFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("SaltnPepperEngine_LOG.txt", 1048576 * 5, 3);
			sinks.emplace_back(logFileSink); 
#endif

			// Creating the loggers
			s_CoreLogger = std::make_shared<spdlog::logger>("SnPLogger", begin(sinks), end(sinks));
			spdlog::register_logger(s_CoreLogger);

			// Configuring the loggers
			spdlog::set_pattern("%^[%T] %v%$");
			s_CoreLogger->set_level(spdlog::level::trace);
#endif

		}

		void Log::OnDestroy()
		{
#if SNP_ENABLE_LOGGING
			s_CoreLogger.reset();
			spdlog::shutdown();
#endif
		}

		void Log::AddSink(std::shared_ptr<spdlog::sinks::sink>& sink)
		{
#if SNP_ENABLE_LOGGING
			s_CoreLogger->sinks().push_back(sink);
			s_CoreLogger->set_pattern("%v%$");
#endif

		}
	}
}