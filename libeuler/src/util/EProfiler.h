#ifndef INCLUDE_LIBEULER_UTIL_PROFILER
#define INCLUDE_LIBEULER_UTIL_PROFILER

#if (defined _WIN32 || defined __APPLE__)
	#include <cstdint>
#endif

/*!
 * \brief This class provides easy-to-use profiling for applications.
 *
 * It utilizes OS-dependant high precision timers to calculate the amount of time that has
 * passed between the object's instantiation and its destruction. Timer precision varies by
 * operating system, but it is safe to assume the accuracy of this timer approaches the
 * nanosecond level.
 *
 * This class is currently implemented on:
 *     Windows
 *     Linux/UNIX
 *     Mac
 */
class EProfiler
{
	public:
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		EProfiler();
		virtual ~EProfiler();
	
		double done();
		
	private:
		#ifdef _WIN32
			int64_t rate;
			double start;
			double end;
		#elif defined __APPLE__
			uint64_t start;
			uint64_t end;
		#else
			double start;
			double end;
		#endif
};

#endif
