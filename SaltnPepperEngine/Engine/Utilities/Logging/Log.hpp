#ifndef LOG_H
#define LOG_H
#include "Core/EngineDefines.hpp"

#define SNP_ENABLE_LOGGING 1

#if SNP_ENABLE_LOGGING

#ifdef SNP_PLATFORM_WINDOWS

#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif // SNP_PLATFORM_WINDOWS


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#define LOG_TRACE(...) SPDLOG_LOGGER_CALL(SaltnPepperEngine::Debug::Log::GetCoreLogger(), spdlog::level::level_enum::trace, __VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_CALL(SaltnPepperEngine::Debug::Log::GetCoreLogger(), spdlog::level::level_enum::info, __VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_CALL(SaltnPepperEngine::Debug::Log::GetCoreLogger(), spdlog::level::level_enum::warn, __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_CALL(SaltnPepperEngine::Debug::Log::GetCoreLogger(), spdlog::level::level_enum::err, __VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CALL(SaltnPepperEngine::Debug::Log::GetCoreLogger(), spdlog::level::level_enum::critical, __VA_ARGS__)

#else

namespace spdlog
{
    namespace sinks
    {
        class sink;
    }
    class logger;
}
#define LOG_TRACE(...) ((void)0)
#define LOG_INFO(...) ((void)0)
#define LOG_WARN(...) ((void)0)
#define LOG_ERROR(...) ((void)0)
#define LOG_CRITICAL(...) ((void)0)

#endif // 

namespace SaltnPepperEngine
{
	namespace  Debug
	{

        class SNP_API Log
        {
        public:

            static void OnInit();
            static void OnDestroy();

#if SNP_ENABLE_LOGGING
            inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
            static void AddSink(std::shared_ptr<spdlog::sinks::sink>& sink);
#endif

        private:
#if SNP_ENABLE_LOGGING
            static std::shared_ptr<spdlog::logger> s_CoreLogger;
#endif

        };
		 

	}
}

#endif // !LOG_H
