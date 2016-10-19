/*
 * euler - A collection of ProjectEuler libraries, tools, and solutions.
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

#ifndef common_structs_BitIterator_HPP
#define common_structs_BitIterator_HPP

#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <type_traits>

#include <boost/optional/optional.hpp>

namespace euler
{
namespace structs
{
template <typename T>
class BitIterator
        : public std::iterator<std::random_access_iterator_tag, bool,
                               std::ptrdiff_t, bool const *, bool const &>
{
public:
	typedef typename std::decay<T>::type input_type;
	static_assert(std::is_arithmetic<value_type>::value,
	              "BitIterator can only be used with arithmetic types.");

	BitIterator();
	explicit BitIterator(input_type i);

	BitIterator(BitIterator const &) = default;
	BitIterator(BitIterator &&) = default;
	BitIterator &operator=(BitIterator const &) = default;
	BitIterator &operator=(BitIterator &&) = default;

	~BitIterator() = default;

	bool operator==(BitIterator const &o) const;
	bool operator!=(BitIterator const &o) const;
	bool operator<(BitIterator const &o) const;
	bool operator<=(BitIterator const &o) const;
	bool operator>(BitIterator const &o) const;
	bool operator>=(BitIterator const &o) const;

	reference operator*() const;
	pointer operator->() const;
	value_type operator[](difference_type n) const;

	BitIterator &operator++();
	BitIterator operator++(int)const;
	BitIterator &operator--();
	BitIterator operator--(int)const;

	BitIterator &operator+=(difference_type n);
	BitIterator operator+(difference_type n) const;
	BitIterator &operator-=(difference_type n);
	BitIterator operator-(difference_type n) const;

	difference_type operator-(BitIterator const &o) const;

private:
	boost::optional<input_type> input;
	difference_type position;
	bool current;

	bool isEnd() const;
};

template <typename T>
BitIterator<T>::BitIterator() : input(boost::none), position(0), current(false)
{
}

template <typename T>
BitIterator<T>::BitIterator(input_type i)
        : input(i), position(0), current(*input & 1)
{
}

template <typename T>
bool BitIterator<T>::operator==(BitIterator const &o) const
{
	if(isEnd() && o.isEnd())
		return true;
	if(isEnd() != o.isEnd())
		return false;
	return input == o.input && position == o.position;
}

template <typename T>
bool BitIterator<T>::operator!=(BitIterator const &o) const
{
	return !(*this == o);
}

template <typename T> bool BitIterator<T>::operator<(BitIterator const &o) const
{
	return *this - o < 0;
}

template <typename T>
bool BitIterator<T>::operator<=(BitIterator const &o) const
{
	return *this - o <= 0;
}

template <typename T> bool BitIterator<T>::operator>(BitIterator const &o) const
{
	return *this - o > 0;
}

template <typename T>
bool BitIterator<T>::operator>=(BitIterator const &o) const
{
	return *this - o >= 0;
}

template <typename T>
typename BitIterator<T>::reference BitIterator<T>::operator*() const
{
	return current;
}

template <typename T>
typename BitIterator<T>::pointer BitIterator<T>::operator->() const
{
	return &current;
}

template <typename T>
typename BitIterator<T>::value_type BitIterator<T>::
operator[](difference_type n) const
{
	return (*input) & (input_type(1) << (position + n));
}

template <typename T> BitIterator<T> &BitIterator<T>::operator++()
{
	++position;
	current = isEnd() ? false : (*this)[0];
	return *this;
}

template <typename T> BitIterator<T> BitIterator<T>::operator++(int)const
{
	BitIterator o(*this);
	++o;
	return o;
}

template <typename T> BitIterator<T> &BitIterator<T>::operator--()
{
	--position;
	current = isEnd() ? false : (*this)[0];
	return *this;
}

template <typename T> BitIterator<T> BitIterator<T>::operator--(int)const
{
	BitIterator o(*this);
	--o;
	return o;
}

template <typename T>
BitIterator<T> &BitIterator<T>::operator+=(difference_type n)
{
	position += n;
	current = isEnd() ? false : (*this)[0];
	return *this;
}

template <typename T>
BitIterator<T> BitIterator<T>::operator+(difference_type n) const
{
	BitIterator o(*this);
	o += n;
	return o;
}

template <typename T>
BitIterator<T> &BitIterator<T>::operator-=(difference_type n)
{
	position -= n;
	current = isEnd() ? false : (*this)[0];
	return *this;
}

template <typename T>
BitIterator<T> BitIterator<T>::operator-(difference_type n) const
{
	BitIterator o(*this);
	o -= n;
	return o;
}

template <typename T>
typename BitIterator<T>::difference_type BitIterator<T>::
operator-(BitIterator const &o) const
{
	assert(isEnd() || o.isEnd() || input == o.input);
	difference_type p = isEnd() ? sizeof(input_type) * CHAR_BIT : position;
	difference_type op =
	        o.isEnd() ? sizeof(input_type) * CHAR_BIT : o.position;
	return p - op;
}

template <typename T> bool BitIterator<T>::isEnd() const
{
	return !input ||
	       position >= static_cast<difference_type>(sizeof(input_type) *
	                                                CHAR_BIT) ||
	       position < 0;
}
}
}

#endif
