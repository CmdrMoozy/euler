#ifndef INCLUDE_LIBEULER_TYPES_ROMAN_NUMERAL_H
#define INCLUDE_LIBEULER_TYPES_ROMAN_NUMERAL_H

#include <string>
#include <cstdint>
#include <map>
#include <set>
#include <utility>

typedef std::pair<std::string, uint64_t> OVPair;

/*!
 * \brief This class implements a roman numeral value container.
 */
class ERomanNumeral
{
	public:
		ERomanNumeral();
		ERomanNumeral(uint64_t v);
		ERomanNumeral(const std::string &v);
		ERomanNumeral(const ERomanNumeral &o);
		
		virtual ~ERomanNumeral();
		
		ERomanNumeral &operator=(const ERomanNumeral &o);
		
		bool operator==(const ERomanNumeral &o) const;
		bool operator<(const ERomanNumeral &o) const;
		bool operator>(const ERomanNumeral &o) const;
		bool operator<=(const ERomanNumeral &o) const;
		bool operator>=(const ERomanNumeral &o) const;
		
		uint64_t getValue() const;
		std::string getStringValue() const;
		
		void setValue(uint64_t v);
		bool parse(const std::string &v);
		
	private:
		struct OVPairComparator {
			bool operator()(const OVPair &a, const OVPair &b);
		};
		
		static const std::map<char, uint64_t> VALUES;
		static const std::set<OVPair, OVPairComparator> OUT_VALUES;
		
		static bool getAdditiveStringValue(const std::string &s, uint64_t *v);
		static bool getSubtractiveStringValue(const std::string &s, uint64_t *v);
		
		uint64_t value;
};

#endif
