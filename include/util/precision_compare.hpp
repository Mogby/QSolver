#ifndef PRECISION_COMPARE_HPP

#define PRECISION_COMPARE_HPP

namespace NUtil {
/// \addtogroup Util
/// @{

/// \brief Reperesents result of comparison
enum ECompareResult {
  CR_LESS = -1, ///< \f$leftValue < rightValue\f$
  CR_EQUAL = 0, ///< \f$leftValue = rightValue\f$
  CR_GREATER = 1 ///< \f$leftValue > rightValue\f$
};

/// \brief Compares real numbers with given precision
/// 
/// Two real numbers are considered equal if
/// \f$|leftValue - rightValue| \le precision\f$.
/// Otherwise, they are compared as usual.
///
/// \param leftValue    left operand value
/// \param rightValue   right operand value
/// \param precision    precision value
///
/// \return \link NUtil::ECompareResult \endlink representing 
///     comparison result
template <typename TReal>
ECompareResult CompareWithPrecision(const TReal leftValue, const TReal rightValue, const TReal precision){
  const auto difference = leftValue - rightValue;
  if (difference < -precision) {
    return CR_LESS;
  } else if (difference > precision) {
    return CR_GREATER;
  } else {
    return CR_EQUAL;
  }
}

/// @}
} // NUtil

#endif // PRECISION_COMPARE_HPP
