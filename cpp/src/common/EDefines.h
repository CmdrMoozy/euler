/*
 * euler - A collection of ProjectEuler solutions, and supporting libraries and
 *tools.
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

// Define our EUNUSED() macro
#ifndef EUNUSED
#if defined(__GNUC__)
#define EUNUSED(x) UNUSED_##x __attribute__((unused))
#else
#define EUNUSED(x)
#endif
#endif

// Define the EFALLTHROUGH annotation, which is used to silence compiler
// warnings when we intentionally want switch() fallthrough behavior.
#ifdef __clang__
#define EFALLTHROUGH [[clang::fallthrough]];
#else
#define EFALLTHROUGH
#endif

#endif
