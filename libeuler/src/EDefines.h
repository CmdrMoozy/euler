/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and tools.
 * Copyright (C) 2013 Axel Rasmussen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
