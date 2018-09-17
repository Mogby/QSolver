#ifndef QSOLVER_HPP

#define QSOLVER_HPP

#include <util/precision_compare.hpp>

#include <vector>

#include <cmath>

namespace NQSolver {
/// \addtogroup QSolver
/// @{

/// \brief Thrown if equation has infinitely many roots
class TInfinitelyManyRootsException : public std::exception {};

/// \brief Represents container of equation roots
template <typename TReal>
using TRoots = std::vector<TReal>;

/// \brief Solves a linear equation \f$ax + b = 0\f$
///
/// \param a                number representing coefficient a value
/// \param b                number representing coefficient b value
/// \param comparePrecision number representing precision of real comparison
///
/// \return container of equation roots in ascending order
///
/// \throw NQSolver::TInfinitelyManyRootsException if equation
///     has infinitely many roots
///
/// \see NUtil::CompareWithPrecision
template <typename TReal>
NQSolver::TRoots<TReal> SolveLinearEquation(const TReal a, const TReal b,
                                            const TReal comparePrecision = 0) {
    if (NUtil::CompareWithPrecision<TReal>(a, 0, comparePrecision) != NUtil::CR_EQUAL) {
        return {-b / a};
    } else if (NUtil::CompareWithPrecision<TReal>(b, 0, comparePrecision) != NUtil::CR_EQUAL){
        return {};
    } else {
        throw NQSolver::TInfinitelyManyRootsException{};
    }
}

/// \brief Solves quadratic equation \f$ax^2 + bx + c = 0\f$
///
/// \param a                number representing coefficient a value
/// \param b                number representing coefficient b value
/// \param c                number representing coefficient c value
/// \param comparePrecision number representing precision of real comparison
///
/// \return container of equation roots in ascending order
///
/// \throw NQSolver::TInfinitelyManyRootsException if equation
///     has infinitely many roots
///
/// \see NUtil::CompareWithPrecision
template <typename TReal>
TRoots<TReal> SolveQuadraticEquation(const TReal a, const TReal b, const TReal c,
                                     const TReal comparePrecision = 0) {
    if (NUtil::CompareWithPrecision<TReal>(a, 0, comparePrecision) == NUtil::CR_EQUAL) {
        return SolveLinearEquation<TReal>(b, c, comparePrecision);
    }

    const TReal discriminant = b * b - 4 * a * c;
    switch (NUtil::CompareWithPrecision<TReal>(discriminant, 0, comparePrecision)) {
        case NUtil::CR_LESS:
            return {};

        case NUtil::CR_EQUAL:
            return {-b / (2 * a)};

        case NUtil::CR_GREATER:
            return {
                (-b - std::sqrt(discriminant)) / (2 * a),
                (-b + std::sqrt(discriminant)) / (2 * a)
            };
    }
}

/// @}
} // NQSolver

#endif // QSOLVER_HPP
