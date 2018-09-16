#include <qsolver.hpp>

#include <util/from_string.hpp>

#include <testing/testlib.hpp>

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

TEST_FUNCTION_BEGIN(TestCompareWithPrecisionEquality)

    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, 0.0, 0.0) == NUtil::CR_EQUAL)
    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, 0.1, 0.0) != NUtil::CR_EQUAL);
    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, 0.1, 0.2) == NUtil::CR_EQUAL);
    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, 0.1, 0.05) != NUtil::CR_EQUAL);

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestCompareWithPrecisionInequality)

    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, 0.1, 0.05) == NUtil::CR_LESS);
    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, 0.1, 0.2) == NUtil::CR_EQUAL);
    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, -0.1, -0.05) == NUtil::CR_GREATER);
    TEST_ASSERT(NUtil::CompareWithPrecision<float>(0.0, -0.1, 0.2) == NUtil::CR_EQUAL);

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestCompareWithPrecision)

    TEST_ASSERT(TestCompareWithPrecisionEquality());
    TEST_ASSERT(TestCompareWithPrecisionInequality());

TEST_FUNCTION_END()


TEST_FUNCTION_BEGIN(TestParseFromString)

    TEST_ASSERT(NUtil::ParseFromString<float>("0.01") == 0.01f);
    TEST_ASSERT(NUtil::ParseFromString<float>("1e9") == 1e9f);
    TEST_ASSERT_THROW(NUtil::ParseFromString<float>("zero point zero one"), NUtil::TParsingException);
    TEST_ASSERT_THROW(NUtil::ParseFromString<float>("0.01 0.01"), NUtil::TParsingException);

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestLinearSolver)

    TEST_ASSERT(NQSolver::SolveLinearEquation<float>(1.0, 0.0) ==
            NQSolver::TRoots<float>{0.0});
    TEST_ASSERT(NQSolver::SolveLinearEquation<float>(1.0, 1.0) ==
            NQSolver::TRoots<float>{-1.0});
    TEST_ASSERT(NQSolver::SolveLinearEquation<float>(0.0, 1.0) ==
            NQSolver::TRoots<float>{});
    TEST_ASSERT_THROW(NQSolver::SolveLinearEquation<float>(0.0, 0.0),
            NQSolver::TInfinitelyManyRootsException);

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestQuadraticSolverDegenerateCase)

    TEST_ASSERT(NQSolver::SolveQuadraticEquation<float>(0.0, 1.0, 0.0) ==
            NQSolver::TRoots<float>{0.0});
    TEST_ASSERT(NQSolver::SolveQuadraticEquation<float>(0.0, 1.0, 1.0) ==
            NQSolver::TRoots<float>{-1.0});
    TEST_ASSERT_THROW(NQSolver::SolveQuadraticEquation<float>(0.0, 0.0, 0.0),
            NQSolver::TInfinitelyManyRootsException);

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestQuadraticSolverCommonCase)

    TEST_ASSERT(NQSolver::SolveQuadraticEquation<float>(1.0, -3.0, 2.0) ==
            NQSolver::TRoots<float>({1.0, 2.0}));
    TEST_ASSERT(NQSolver::SolveQuadraticEquation<float>(1.0, -2.0, 1.0) ==
            NQSolver::TRoots<float>{1.0});
    TEST_ASSERT(NQSolver::SolveQuadraticEquation<float>(1.0, 1.0, 1.0) ==
            NQSolver::TRoots<float>{});

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestQuadraticSolver)

    TEST_ASSERT(TestQuadraticSolverDegenerateCase());
    TEST_ASSERT(TestQuadraticSolverCommonCase());

TEST_FUNCTION_END()

TEST_FUNCTION_BEGIN(TestMain)

    TEST_ASSERT(TestCompareWithPrecision());
    TEST_ASSERT(TestParseFromString());
    TEST_ASSERT(TestLinearSolver());
    TEST_ASSERT(TestQuadraticSolver());

TEST_FUNCTION_END()

int main() {
    if (!TestMain()) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
