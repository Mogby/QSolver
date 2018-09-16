#ifndef TEST_LIB_HPP

#define TEST_LIB_HPP

/// \addtogroup Testing
/// @{

/// \brief Opens definition of test function
///
/// Defines a function `bool functionName()`.
/// You can use TEST_ASSERT(expression) and 
/// TEST_ASSERT_THROW(expression, exception_type)
/// macros in its body.
///
/// The function returns `false` if at least one of its test
/// assertions failed.
/// Otherwise it returns `true`.
///
/// You shouldn't use variables named `__testSuccess__` or 
/// `__testFunctionName__` inside the test function body
/// as they are reserved for internal use.
///
/// \param functionName name of test function
///
/// \see TEST_FUNCTION_END()
#define TEST_FUNCTION_BEGIN(functionName) \
    bool functionName() { \
        bool __testSuccess__ = true; \
        std::string __testFunctionName__ = #functionName;

/// \brief Closes definition of test function
///
/// Every TEST_FUNCTION_BEGIN(functionName) macro
/// should be closed with this.
#define TEST_FUNCTION_END() \
        return __testSuccess__; \
    }

/// \brief Prints debug message
///
/// Prints the given message with debug information:
/// file, function name and line from which the macro
/// was invoked.
///
/// Can only be used inside a test function.
///
/// \param message message to print
#define TEST_PRINT(message) \
    cerr << "In file " __FILE__ << endl; \
    cerr << "In function " << __testFunctionName__ << " at line " << __LINE__ << endl; \
    cerr << "\t" << (message) << endl;

/// \brief Tests if expression is `true`
///
/// If the test has failed, prints an error message.
///
/// Can only be used inside a test function.
///
/// \param expression expression to test
#define TEST_ASSERT(expression) \
    if (!(expression)) { \
        TEST_PRINT("Assertion failed: " #expression); \
        __testSuccess__ = false; \
    } 

/// \brief Tests if expression throws `exception_type`
///
/// If the test has failed, prints an error message.
///
/// Can only be used inside a test function.
///
/// \param expression expression that should throw
/// \param exception_type expected type of thrown exception
#define TEST_ASSERT_THROW(expression, exception_type) \
    bool threw##__LINE__ = false; \
    try { \
        expression; \
    } catch(const exception_type&) { \
        threw##__LINE__ = true; \
    } \
    if (!threw##__LINE__) { \
        TEST_PRINT("Throw assertion failed: " #expression); \
        __testSuccess__ = false; \
    }

/// @}

#endif // TEST_LIB_HPP
