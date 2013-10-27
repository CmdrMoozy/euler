#ifndef INCLUDE_LIBEULER_UTIL_BYTE_ARRAY_H
#define INCLUDE_LIBEULER_UTIL_BYTE_ARRAY_H

#include <cstdint>

#include "../util/EArray.h"
#include "../EExceptions.h"

// Typedef 'byte' for EByteArray.
typedef uint8_t byte;

/*!
 * \brief This class represents a string of bits.
 *
 * It can be operated on just like any smaller container like an int or a long, but it can be
 * an arbitrary amount of bytes in length.
 */
class EByteArray : public EArray<byte>
{
	public:
		/*!
		 * This enum defines the policy that would be used when filling-in new space in a
		 * bitstring object, for instance, while resizing or while initializing a new object.
		 *
		 * "Preserve" means that old data (e.g., while resizing) will be preserved, "Set"
		 * means that bits will be set to "1" and "Clear" means bits will be set to "0."
		 */
		enum FillPolicy
		{
			Set,
			Clear,
			PreserveSet,
			PreserveClear
		};
		
#ifdef LIBEULER_DEBUG
		static void doTestSuite();
#endif
		
		static int getMinimumByteLength(int b);
		
		EByteArray(int l = 0, EByteArray::FillPolicy p = EByteArray::Clear);
		virtual ~EByteArray();
		
		bool operator==(const EByteArray &o) const;
		bool operator<(const EByteArray &o) const;
		bool operator<=(const EByteArray &o) const;
		bool operator>(const EByteArray &o) const;
		bool operator>=(const EByteArray &o) const;
		
		int bitSize() const;
		void resize(int n, EByteArray::FillPolicy p);
		
		bool bitAt(int i) const throw(EOutOfBoundsException &);
		void setBitAt(int i, bool v) throw(EOutOfBoundsException &);
		
		void flipBitAt(int i) throw(EOutOfBoundsException &);
		
		void clearBits();
		void setBits();
		int population() const;
		
		void leftShift(int n);
		void leftRotate(int n);
		void rightShift(int n);
		void rightRotate(int n);
		
		void bitwiseComplement();
		
		void bitwiseAnd(const EByteArray &o);
		void bitwiseOr(const EByteArray &o);
		void bitwiseXor(const EByteArray &o);
		
		void bitwiseAnd(uint32_t v, int lS = 0);
		void bitwiseOr(uint32_t v, int lS = 0);
		void bitwiseXor(uint32_t v, int lS = 0);
		
	private:
		int compare(const EByteArray &o) const;
		
		int bitOffset(int by, int bi) const;
		int byteOffset(int i) const;
		int relativeBitOffset(int i) const;
	
		bool hasBitsSet() const;
};

#endif
