#include "EExceptions.h"

/****************************************************************************************************
 * EException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EException::EException(const std::string &wh)
	: w(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EException::~EException()
	throw()
{
}

/*!
 * This is the accessor function that returns our exception string. It returns a cstring, because
 * std::string's copy constructor can throw an exception. This function MUST NOT throw any exceptions.
 *
 * \return A C-string version of our exception text.
 */
const char *EException::what() const
	throw()
{
	return w.c_str();
}

/****************************************************************************************************
 * EAssertionException
 ****************************************************************************************************/

EAssertionException::EAssertionException(const std::string &wh)
	: EException(wh)
{
}

EAssertionException::~EAssertionException()
	throw()
{
}

/****************************************************************************************************
 * EStringFormatException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EStringFormatException::EStringFormatException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EStringFormatException::~EStringFormatException()
	throw()
{
}

/****************************************************************************************************
 * EOutOfBoundsException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EOutOfBoundsException::EOutOfBoundsException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EOutOfBoundsException::~EOutOfBoundsException()
	throw()
{
}

/****************************************************************************************************
 * EValueRangeException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EValueRangeException::EValueRangeException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EValueRangeException::~EValueRangeException()
	throw()
{
}

/****************************************************************************************************
 * EOverflowException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EOverflowException::EOverflowException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EOverflowException::~EOverflowException()
	throw()
{
}

/****************************************************************************************************
 * EUnderflowException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EUnderflowException::EUnderflowException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EUnderflowException::~EUnderflowException()
	throw()
{
}

/****************************************************************************************************
 * EDivideByZeroException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EDivideByZeroException::EDivideByZeroException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EDivideByZeroException::~EDivideByZeroException()
	throw()
{
}

/****************************************************************************************************
 * EIOException
 ****************************************************************************************************/

/*!
 * This is a standard constructor for our class. It simply sets our exception text to the given string.
 *
 * \param what The exception text to use.
 */
EIOException::EIOException(const std::string &wh)
	: EException(wh)
{
}

/*!
 * This is our standard virtual destructor that cleans up our class. It MUST NOT throw any exceptions.
 */
EIOException::~EIOException()
	throw()
{
}
