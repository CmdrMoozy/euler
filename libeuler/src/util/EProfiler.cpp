#include "EProfiler.h"

#ifdef _WIN32
	#include <windows.h>
#elif defined __APPLE__
	#include <mach/mach.h>
	#include <mach/mach_time.h>
	#include <CoreServices/CoreServices.h>
	#include <unistd.h>
#else
	#include <ctime>
	
	#ifdef LIBEULER_DEBUG
		#include <unistd.h>
	#endif
#endif

#ifdef LIBEULER_DEBUG
	#include <iostream>
	#include <cmath>
	
	#include "EDefines.h"
	#include "EExceptions.h"
#endif

#ifdef LIBEULER_DEBUG
/*!
 * This function implements our test suite for this class. It uses non-abort()'ing
 * assertions, and merely prints the result to stdout.
 */
void EProfiler::doTestSuite()
{
	bool success;
	
	std::cout << "\tTesting 'EProfiler'...\t\t\t";
	try
	{
		success = true;
		
		// Make sure timing on a one-second sleep is fairly accurate.
		
		for(int i = 0; i < 10; ++i)
		{
			EProfiler p;
			
			#ifdef _WIN32
				Sleep(1000);
			#else
				sleep(1);
			#endif
			
			double t = fabs(1.0 - p.done());
			EASSERT(t < 0.1);
		}
		
		// Make sure timing on a ten-second sleep is fairly accurate as well.
		
		EProfiler p;
		#ifdef _WIN32
			Sleep(10000);
		#else
			sleep(10);
		#endif
		double lt = fabs(10.0 - p.done());
		EASSERT(lt < 0.1);
	}
	catch(EAssertionException &e)
	{
		success = false;
	}
	
	// Print out our results.
	if(success)
		std::cout << "[ OK ]\n";
	else
		std::cout << "[FAIL]\n";
}
#endif

/*!
 * This is our constructor, which records our "starting" time.
 */
EProfiler::EProfiler()
	: start(1.0), end(0.0)
{
	#ifdef _WIN32
		
		LARGE_INTEGER li;
		if(QueryPerformanceFrequency(&li))
		{
			rate = static_cast<int64_t>(li.QuadPart);
			
			if(QueryPerformanceCounter(&li))
				start = static_cast<double>(li.QuadPart) / static_cast<double>(rate);
		}
		else
		{
			rate = 1;
		}
	
	#elif defined __APPLE__
	
		start = mach_absolute_time();
		
	#else
		
		struct timespec s;
	
		if(clock_gettime(CLOCK_MONOTONIC, &s) == 0)
			start = static_cast<double>(s.tv_sec) + (static_cast<double>(s.tv_nsec) / 1000000000.0);
		else
			start = 1.0;
		
	#endif
}

/*!
 * This is our destructor, which cleans up and destroys our object.
 */
EProfiler::~EProfiler()
{
}

/*!
 * The value returned is a floating point seconds value, indicating the time that passed between when our
 * constructor and destructor were called. Note that we do not take into account the time required to
 * make the clock calls themselves (this is assumed to be negligible).
 *
 * Note that this function can be called more than once, if desired. The start time is not updated, so the
 * result returned will be a running count of execution time.
 *
 * If an error occurs, this function returns -1.0.
 *
 * \return How many seconds have passed between object instantiation and "now."
 */
double EProfiler::done()
{
	#ifdef _WIN32
		
		LARGE_INTEGER li;
		
		if(QueryPerformanceCounter(&li))
			end = static_cast<double>(li.QuadPart) / static_cast<double>(rate);
		else
			start = 1.0;
	
		return (end - start);
	
	#elif defined __APPLE__
	
		end = mach_absolute_time();
		
		uint64_t elapsed = end - start;
		Nanoseconds elapsedNano = AbsoluteToNanoseconds( *(AbsoluteTime *) &elapsed );
		elapsed = * (uint64_t *) &elapsedNano;
		
		double d = elapsed;
		return d / 1000000000.0;
	
	#else
	
		struct timespec e;
		
		if(clock_gettime(CLOCK_MONOTONIC, &e) == 0)
		{
			end = static_cast<double>(e.tv_sec) + (static_cast<double>(e.tv_nsec) / 1000000000.0);
		}
		else
		{
			start = 1.0;
			end = 0.0;
		}
		
		return (end - start);
		
	#endif
}
