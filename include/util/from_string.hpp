#ifndef FROM_STRING_HPP

#define FROM_STRING_HPP

#include <exception>
#include <sstream>
#include <string>


namespace NUtil {
/// \addtogroup Util
/// @{

/// \brief Thrown if parsing did not succeed
class TParsingException : public std::exception {};

/// \brief Parses value of given type from string
///
/// \param string string to parse
///
/// \return `TParsedType` representing parsed value
/// 
/// \throw NUtil::TParsingException if the string could not be parsed
///     or some part of the string was left unparsed
template <typename TParsedType>
TParsedType ParseFromString(const std::string& string) {
    std::stringstream converter;
    converter << string;

    TParsedType parsedValue;
    if (!(converter >> parsedValue) ||
        !converter.eof()) {
        throw TParsingException{};
    }

    return parsedValue;
}

/// @}
} // NUtil

#endif // FROM_STRING_HPP
