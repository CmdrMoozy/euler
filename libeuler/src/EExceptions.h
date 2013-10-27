#ifndef INCLUDE_LIBEULER_EXCEPTIONS_H
#define INCLUDE_LIBEULER_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/*!
 * \brief This class is our base class for all of our exceptions.
 *
 * It is present so one can catch all exceptions generated by libsquare, while avoiding
 * getting standard C++ exceptions (i.e., catch(EException &e) as opposed to
 * catch(std::exception &e)).
 */
class EException : public std::exception
{
	public:
		explicit EException(const std::string &wh);
		virtual ~EException() throw();
	
		virtual const char *what() const throw();
	
	private:
		std::string w;
};

/*!
 * \brief This class represents an exception thrown due to an assertion failure.
 *
 * It is designed to be thrown (primarily) from our EASSERT() macro defined in EDefines.h.
 */
class EAssertionException : public EException
{
	public:
		explicit EAssertionException(const std::string &wh);
		virtual ~EAssertionException() throw();
};

/*!
 * \brief This class represents an exception thrown due to a malformed string.
 *
 * It is designed to be thrown, for example, by a parser function
 * that receives some kind of unexpected or otherwise invalid input. It subclasses
 * std::exception, so it can be caught with a general try/catch block.
 */
class EStringFormatException : public EException
{
	public:
		explicit EStringFormatException(const std::string &wh);
		virtual ~EStringFormatException() throw();
};

/*!
 * \brief This class represents an exception being thrown due to an index being out of bounds.
 *
 * It is designed to be thrown, for example, by a function that is
 * accessing an array that encounters an index that is out-of-bounds. It subclasses
 * std::exception, so it can be caught with a general try/catch block.
 */
class EOutOfBoundsException : public EException
{
	public:
		explicit EOutOfBoundsException(const std::string &wh);
		virtual ~EOutOfBoundsException() throw();
};

/*!
 * \brief This class represents an exception being thrown due to a value being out of range.
 *
 * It is designed to be thrown, for example, by a function that takes some
 * numerical input which has specific restrictions on the input value which encounters a value
 * which is invalid. It subclasses std::exception, so it can be caught with a general try/catch
 * block.
 */
class EValueRangeException : public EException
{
	public:
		explicit EValueRangeException(const std::string &wh);
		virtual ~EValueRangeException() throw();
};

/*!
 * \brief This class represents an exception being thrown due to a value being too large.
 *
 * It is designed to be thrown, for example, by a function that does some calculation whose
 * result can end up being too large for the function to handle. It subclasses std::exception,
 * so it can be caught with a general try/catch block.
 */
class EOverflowException : public EException
{
	public:
		explicit EOverflowException(const std::string &wh);
		virtual ~EOverflowException() throw();
};

/*!
 * \brief This class represents an exception being thrown due to a value being too small.
 *
 * It is designed to be thrown, for example, by a function that does some calculation whose
 * result can end up being too small for the function to handle. It subclasses std::exception,
 * so it can be caught with a general try/catch block.
 */
class EUnderflowException : public EException
{
	public:
		explicit EUnderflowException(const std::string &wh);
		virtual ~EUnderflowException() throw();
};

/*!
 * \brief This class represents an exception being thrown due to an attempt to divide by zero.
 *
 * It is fairly specific about what the error is, however the cause can be several different
 * things - perhaps a divide or modulus operation, for instance. It subclasses std::exception,
 * so it can be caught with a general try/catch block.
 */
class EDivideByZeroException : public EException
{
	public:
		explicit EDivideByZeroException(const std::string &wh);
		virtual ~EDivideByZeroException() throw();
};

/*!
 * \brief This class represents an exception being thrown due to an input/output error.
 *
 * This exception could be thrown by anything, for example, from being unable to create a new
 * directory to being unable to open a file for reading. In theory, the what() text should
 * provide a more specific explanation for the exception.
 */
class EIOException : public EException
{
	public:
		explicit EIOException(const std::string &wh);
		virtual ~EIOException() throw();
};

#endif
