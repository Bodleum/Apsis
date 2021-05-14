#include "apch.h"
#include "Logger.h"
	//#include <spdlog/spdlog.h>
	//#include <spdlog/fmt/ostr.h>

#pragma warning(push, 0)
	#include <spdlog/sinks/stdout_color_sinks.h>
	#include <spdlog/sinks/basic_file_sink.h>
#pragma warning pop

namespace A {

	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Logger::s_CoreAssertLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientAssertLogger;

	void A::Logger::Init()
	{
		AP_PROFILE_FN();

		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Apsis.log", true));

		logSinks[0]->set_pattern("%^[%r] %n:\t%v%$");
		logSinks[1]->set_pattern("[%r] [%l] %n:\t%v");

		s_CoreLogger = std::make_shared<spdlog::logger>("Apsis", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("Client", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);

		// ---   Asserts   ---
		s_CoreAssertLogger = std::make_shared<spdlog::logger>("Apsis Assert", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreAssertLogger);
		s_CoreAssertLogger->set_level(spdlog::level::trace);
		s_CoreAssertLogger->flush_on(spdlog::level::trace);

		s_ClientAssertLogger = std::make_shared<spdlog::logger>("Client Assert", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientAssertLogger);
		s_ClientAssertLogger->set_level(spdlog::level::trace);
		s_ClientAssertLogger->flush_on(spdlog::level::trace);
	}

}