CFLAGS_DEBUG_STATIC = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -pipe -g -O0 -std=c++0x -DLIBEULER_DEBUG
CFLAGS_DEBUG_DYNAMIC = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -fPIC -pipe -g -O0 -std=c++0x -DLIBEULER_DEBUG
CFLAGS_RELEASE_STATIC = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -pipe -fomit-frame-pointer -O2 -std=c++0x
CFLAGS_RELEASE_DYNAMIC = -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -fPIC -pipe -fomit-frame-pointer -O2 -std=c++0x

IFLAGS = -Isrc
LDFLAGS = -lm -lrt -lgmp -lgmpxx -lmpfr

CC = g++ -c
LD = g++
AR = ar cqs

OBJECT_PREFIX = obj/
OBJECTS = $(OBJECT_PREFIX)EExceptions.o \
	$(OBJECT_PREFIX)euler_ECircularPrimeSieve.o \
	$(OBJECT_PREFIX)euler_EFastTotient.o \
	$(OBJECT_PREFIX)euler_ENumberGrid.o \
	$(OBJECT_PREFIX)euler_EPoker.o \
	$(OBJECT_PREFIX)euler_ESpiral.o \
	$(OBJECT_PREFIX)euler_ESudoku.o \
	$(OBJECT_PREFIX)euler_ETriangleStructure.o \
	$(OBJECT_PREFIX)geodesy_EGeoCoord.o \
	$(OBJECT_PREFIX)geodesy_ELatLonValue.o \
	$(OBJECT_PREFIX)graph_EGridGraph.o \
	$(OBJECT_PREFIX)graph_EGridVertex.o \
	$(OBJECT_PREFIX)math_EExactCover.o \
	$(OBJECT_PREFIX)math_EFactorization.o \
	$(OBJECT_PREFIX)math_EMath.o \
	$(OBJECT_PREFIX)math_EPrimeSieve.o \
	$(OBJECT_PREFIX)types_EBigInteger.o \
	$(OBJECT_PREFIX)types_EDigitInteger.o \
	$(OBJECT_PREFIX)types_EFraction.o \
	$(OBJECT_PREFIX)types_ERightTriangle.o \
	$(OBJECT_PREFIX)types_ETriangle.o \
	$(OBJECT_PREFIX)util_EBitwise.o \
	$(OBJECT_PREFIX)util_EByteArray.o \
	$(OBJECT_PREFIX)util_EDate.o \
	$(OBJECT_PREFIX)util_EProfiler.o \
	$(OBJECT_PREFIX)util_EString.o

STATIC_LIB = libeuler.a
DYNAMIC_LIB = libeuler.so

TEST = ETests

# Meta-targets

all: release-dynamic

debug-static: dir-prepare
debug-static: CFLAGS = $(CFLAGS_DEBUG_STATIC)
debug-static: $(OBJECTS) $(STATIC_LIB)

debug-dynamic: dir-prepare
debug-dynamic: CFLAGS = $(CFLAGS_DEBUG_DYNAMIC)
debug-dynamic: $(OBJECTS) $(DYNAMIC_LIB)

release-static: dir-prepare
release-static: CFLAGS = $(CFLAGS_RELEASE_STATIC)
release-static: $(OBJECTS) $(STATIC_LIB)

release-dynamic: dir-prepare
release-dynamic: CFLAGS = $(CFLAGS_RELEASE_DYNAMIC)
release-dynamic: $(OBJECTS) $(DYNAMIC_LIB)

test: CFLAGS = $(CFLAGS_DEBUG_STATIC)
test: $(TEST)

# Object file rules

$(OBJECT_PREFIX)EExceptions.o: src/EExceptions.h src/EExceptions.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/EExceptions.cpp -o $(OBJECT_PREFIX)EExceptions.o

$(OBJECT_PREFIX)euler_ECircularPrimeSieve.o: src/euler/ECircularPrimeSieve.h src/euler/ECircularPrimeSieve.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/ECircularPrimeSieve.cpp -o $(OBJECT_PREFIX)euler_ECircularPrimeSieve.o

$(OBJECT_PREFIX)euler_EFastTotient.o: src/euler/EFastTotient.h src/euler/EFastTotient.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/EFastTotient.cpp -o $(OBJECT_PREFIX)euler_EFastTotient.o

$(OBJECT_PREFIX)euler_ENumberGrid.o: src/euler/ENumberGrid.h src/euler/ENumberGrid.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/ENumberGrid.cpp -o $(OBJECT_PREFIX)euler_ENumberGrid.o

$(OBJECT_PREFIX)euler_EPoker.o: src/euler/EPoker.h src/euler/EPoker.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/EPoker.cpp -o $(OBJECT_PREFIX)euler_EPoker.o

$(OBJECT_PREFIX)euler_ESpiral.o: src/euler/ESpiral.h src/euler/ESpiral.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/ESpiral.cpp -o $(OBJECT_PREFIX)euler_ESpiral.o

$(OBJECT_PREFIX)euler_ESudoku.o: src/euler/ESudoku.h src/euler/ESudoku.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/ESudoku.cpp -o $(OBJECT_PREFIX)euler_ESudoku.o

$(OBJECT_PREFIX)euler_ETriangleStructure.o: src/euler/ETriangleStructure.h src/euler/ETriangleStructure.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/euler/ETriangleStructure.cpp -o $(OBJECT_PREFIX)euler_ETriangleStructure.o

$(OBJECT_PREFIX)geodesy_EGeoCoord.o: src/geodesy/EGeoCoord.h src/geodesy/EGeoCoord.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/geodesy/EGeoCoord.cpp -o $(OBJECT_PREFIX)geodesy_EGeoCoord.o

$(OBJECT_PREFIX)geodesy_ELatLonValue.o: src/geodesy/ELatLonValue.h src/geodesy/ELatLonValue.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/geodesy/ELatLonValue.cpp -o $(OBJECT_PREFIX)geodesy_ELatLonValue.o

$(OBJECT_PREFIX)graph_EGridGraph.o: src/graph/EGridGraph.h src/graph/EGridGraph.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/graph/EGridGraph.cpp -o $(OBJECT_PREFIX)graph_EGridGraph.o

$(OBJECT_PREFIX)graph_EGridVertex.o: src/graph/EGridVertex.h src/graph/EGridVertex.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/graph/EGridVertex.cpp -o $(OBJECT_PREFIX)graph_EGridVertex.o

$(OBJECT_PREFIX)math_EExactCover.o: src/math/EExactCover.h src/math/EExactCover.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/math/EExactCover.cpp -o $(OBJECT_PREFIX)math_EExactCover.o

$(OBJECT_PREFIX)math_EFactorization.o: src/math/EFactorization.h src/math/EFactorization.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/math/EFactorization.cpp -o $(OBJECT_PREFIX)math_EFactorization.o

$(OBJECT_PREFIX)math_EMath.o: src/math/EMath.h src/math/EMath.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/math/EMath.cpp -o $(OBJECT_PREFIX)math_EMath.o

$(OBJECT_PREFIX)math_EPrimeSieve.o: src/math/EPrimeSieve.h src/math/EPrimeSieve.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/math/EPrimeSieve.cpp -o $(OBJECT_PREFIX)math_EPrimeSieve.o

$(OBJECT_PREFIX)types_EBigInteger.o: src/types/EBigInteger.h src/types/EBigInteger.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/types/EBigInteger.cpp -o $(OBJECT_PREFIX)types_EBigInteger.o

$(OBJECT_PREFIX)types_EDigitInteger.o: src/types/EDigitInteger.h src/types/EDigitInteger.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/types/EDigitInteger.cpp -o $(OBJECT_PREFIX)types_EDigitInteger.o

$(OBJECT_PREFIX)types_EFraction.o: src/types/EFraction.h src/types/EFraction.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/types/EFraction.cpp -o $(OBJECT_PREFIX)types_EFraction.o

$(OBJECT_PREFIX)types_ERightTriangle.o: src/types/ERightTriangle.h src/types/ERightTriangle.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/types/ERightTriangle.cpp -o $(OBJECT_PREFIX)types_ERightTriangle.o

$(OBJECT_PREFIX)types_ETriangle.o: src/types/ETriangle.h src/types/ETriangle.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/types/ETriangle.cpp -o $(OBJECT_PREFIX)types_ETriangle.o

$(OBJECT_PREFIX)util_EBitwise.o: src/util/EBitwise.h src/util/EBitwise.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/util/EBitwise.cpp -o $(OBJECT_PREFIX)util_EBitwise.o

$(OBJECT_PREFIX)util_EByteArray.o: src/util/EByteArray.h src/util/EByteArray.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/util/EByteArray.cpp -o $(OBJECT_PREFIX)util_EByteArray.o

$(OBJECT_PREFIX)util_EDate.o: src/util/EDate.h src/util/EDate.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/util/EDate.cpp -o $(OBJECT_PREFIX)util_EDate.o

$(OBJECT_PREFIX)util_EProfiler.o: src/util/EProfiler.h src/util/EProfiler.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/util/EProfiler.cpp -o $(OBJECT_PREFIX)util_EProfiler.o

$(OBJECT_PREFIX)util_EString.o: src/util/EString.h src/util/EString.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) src/util/EString.cpp -o $(OBJECT_PREFIX)util_EString.o

# Library rules

$(STATIC_LIB): $(OBJECTS)
	$(AR) release/lib/$(STATIC_LIB) $(OBJECTS)
	cp -R src/* release/include/libeuler/
	find release/include/libeuler/ -type f -iname "*.c" -or -iname "*.cpp" -exec rm -fr {} \;

$(DYNAMIC_LIB) : $(OBJECTS)
	$(LD) -shared -Wl,-soname,$(DYNAMIC_LIB) $(LDFLAGS) -o release/lib/$(DYNAMIC_LIB) $(OBJECTS) -lc
	cp -R src/* release/include/libeuler/
	find release/include/libeuler/ -type f -iname "*.c" -or -iname "*.cpp" -exec rm -fr {} \;

# Test suite rules

$(TEST): $(OBJECTS) src/ETests.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) src/ETests.cpp -o $(OBJECT_PREFIX)ETests.o
	$(LD) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(OBJECT_PREFIX)ETests.o -o ETests

# Extra rules

dir-prepare:
	if [ ! -d "obj" ] ; then mkdir obj ; fi
	if [ ! -d "release/lib" ] ; then mkdir -p release/lib ; fi
	if [ ! -d "release/include/libeuler" ] ; then mkdir -p release/include/libeuler ; fi
	if [ ! -d "docs/doxygen" ] ; then mkdir -p docs/doxygen ; fi

doc:
	doxygen Doxyfile

clean:
	@rm -fr docs/doxygen/*
	@rm -fr obj/*
	@rm -fr release/include/libeuler/*
	@rm -fr release/lib/*
	@rm -fr $(TEST)
