#pragma once

#include <chrono>
#include <fstream>
#include <string>
#include <mutex>

/*
* Instrumentor from Hazel
* https://github.com/TheCherno/Hazel
*/

namespace A {

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		void EndSession();

		void WriteProfile(const ProfileResult& result);

		static inline Instrumentor& Get() { static Instrumentor instance; return instance; }

	private:
		Instrumentor();
		virtual ~Instrumentor();

		void WriteHeader();
		void WriteFooter();

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession();

	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name);
		~InstrumentationTimer();

		void Stop();

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#if (defined(AP_DEBUG) || defined(AP_RELEASE))
	#define AP_PROFILE 1
#endif

#if AP_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define AP_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define AP_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define AP_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define AP_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define AP_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define AP_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define AP_FUNC_SIG __func__
	#else
		#define AP_FUNC_SIG "AP_FUNC_SIG unknown!"
	#endif

	#define AP_PROFILE_BEGIN_SESSION(name, filepath) ::A::Instrumentor::Get().BeginSession(name, filepath)
	#define AP_PROFILE_END_SESSION() ::A::Instrumentor::Get().EndSession()
	#define AP_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::A::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												   ::A::InstrumentationTimer timer##line(fixedName##line.Data)
	#define AP_PROFILE_SCOPE_LINE(name, line) AP_PROFILE_SCOPE_LINE2(name, line)
	#define AP_PROFILE_SCOPE(name) AP_PROFILE_SCOPE_LINE(name, __LINE__)
	#define AP_PROFILE_FN() AP_PROFILE_SCOPE(AP_FUNC_SIG)
#else
	#define AP_PROFILE_BEGIN_SESSION(name, filepath)
	#define AP_PROFILE_END_SESSION()
	#define AP_PROFILE_SCOPE(name)
	#define AP_PROFILE_FN()
#endif