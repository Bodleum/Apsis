#pragma once
#pragma warning(push, 0)
	#include <memory>

	#include <spdlog/spdlog.h>
	#include <spdlog/fmt/ostr.h>
#pragma warning pop

/*
* Shamelessly stolen from Hazel engine
* https://github.com/TheCherno/Hazel
*/

namespace A {

	class Logger
	{
	public:
		static void Init();

		static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		static inline std::shared_ptr<spdlog::logger>& GetCoreAssertLogger() { return s_CoreAssertLogger; }
		static inline std::shared_ptr<spdlog::logger>& GetClientAssertLogger() { return s_ClientAssertLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreAssertLogger;
		static std::shared_ptr<spdlog::logger> s_ClientAssertLogger;
	};

}

#define AP_TRACE_C(...)	::A::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define AP_INFO_C(...)	::A::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define AP_WARN_C(...)	::A::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define AP_ERROR_C(...)	::A::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define AP_CRIT_C(...)	::A::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define AP_TRACE(...)	::A::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define AP_INFO(...)	::A::Logger::GetClientLogger()->info(__VA_ARGS__)
#define AP_WARN(...)	::A::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define AP_ERROR(...)	::A::Logger::GetClientLogger()->error(__VA_ARGS__)
#define AP_CRIT(...)	::A::Logger::GetClientLogger()->critical(__VA_ARGS__)

// ---   Asserts   ---
#if defined(AP_DEBUG) || defined(AP_RELEASE)
	#define AP_ASSERT_C(expr, msg, ...) if (!(expr)) { ::A::Logger::GetCoreAssertLogger()->critical(msg, __VA_ARGS__); }
	#define AP_ASSERT_NOMSG_C(expr) if (!(expr)) { ::A::Logger::GetCoreAssertLogger()->critical("Assertion fail: {0}", #expr); }

	#define AP_ASSERT(expr, msg, ...) if (!(expr)) { ::A::Logger::GetClientAssertLogger()->critical(msg, __VA_ARGS__); }
	#define AP_ASSERT_NOMSG(expr) if (!(expr)) { ::A::Logger::GetClientAssertLogger()->critical("Assertion fail: {0}", #expr); }
#else
	#define AP_ASSERT_C(expr, msg, ...)
	#define AP_ASSERT_NOMSG_C(expr)

	#define AP_ASSERT(expr, msg, ...)
	#define AP_ASSERT_NOMSG(expr)
#endif // AP_DEBUG