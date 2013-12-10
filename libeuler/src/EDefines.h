#ifndef INCLUDE_LIBEULER_DEFINES_H
#define INCLUDE_LIBEULER_DEFINES_H

	#include <iostream>
	
	#include "EExceptions.h"
	
	// Disable some warnings we don't care about on win32.
	#ifdef _WIN32
		#pragma warning( disable : 4290 ) // Exception specification on functions.
	#endif
	
	// We define a macro to get the absolute value of a number.
	#define EABS(a) ( (a) < 0 ? (-(a)) : (a) )
	
	/*
	 * Define our ELUNUSED macro, which is used on win32 to suppress the "unreferenced local
	 * variable" warning (4101) in cases where we are very intentionally NOT referencing said
	 * variable.
	 */
	#ifndef ELUNUSED
		#ifdef _WIN32
			#define ELUNUSED(x) x;
		#else
			#define ELUNUSED(x)
		#endif
	#endif

	// Define our EUNUSED() macro
	#ifndef EUNUSED
		#if defined(__GNUC__)
			#define EUNUSED(x) UNUSED_ ## x __attribute__((unused))
		#else
			#define EUNUSED(x)
		#endif
	#endif
	
	/*
	 * This macro is designed to give us access to the name of our current function, for debugging
	 * purposes.
	 *
	 * This macro is __E_PRETTY_FUNCTION__, which is supposed to provide the name of the function
	 * it is evaluated in, for use in debugging output.
	 *
	 * In fairly recent versions of GCC, __PRETTY_FUNCTION__ is defined. In case it isn't,
	 * we try some fallbacks - __FUNCTION__, which is defined in older GCC versions and also
	 * in MSVC, or __func__, which is defined as part of the C99 standard and should be present
	 * in ANY semi-modern compiler.
	 */
	#ifndef __E_PRETTY_FUNCTION__
		#ifdef __PRETTY_FUNCTION__
			#define __E_PRETTY_FUNCTION__ __PRETTY_FUNCTION__
		#elif defined(__FUNCTION__)
			#define __E_PRETTY_FUNCTION__ __FUNCTION__
		#else
			#define __E_PRETTY_FUNCTION__ __func__
		#endif
	#endif
	
	// This macro prints out information about the given exception and then aborts() (for debugging purposes).
	#define EDIE_LOGIC(exception) \
		std::cerr << "\nDEBUG: LOGIC ERROR: " << __E_PRETTY_FUNCTION__ << " EXCEPTION: " << \
			exception.what() << "\n"; \
		abort();
	
	// Replacement for cassert that doesn't abort() on failure.
	#define EASSERT(assertion) \
		if(!(assertion)) \
			throw EAssertionException("Assertion '" #assertion "' failed.\n"); \

#endif
