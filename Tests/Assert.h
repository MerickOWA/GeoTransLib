#include "WinUnit.h"

#define WIN_ASSERT_EQUAL_TOL( expected, actual, tolerance, ... ) Assert::AreEqual( TSTRING(expected), expected, TSTRING(actual), actual, tolerance, __TFILE__, __LINE__, __VA_ARGS__ )

#pragma warning ( disable: 4624 )

class Assert : public WinUnit::Assert
{
public:

  template <class T, class U, class V>
  static void AreEqual( const TCHAR* expectedExpressionString, const T& expectedExpressionValue,
                        const TCHAR* actualExpressionString, const U& actualExpressionValue,
                        const V& toleranceExpressionValue,
                        const TCHAR* fileName, int lineNumber,
                        const TCHAR* message = NULL, ...);
};

template <class T, class U, class V>
void Assert::AreEqual( const TCHAR* expectedExpressionString, const T& expectedExpressionValue,
                       const TCHAR* actualExpressionString, const U& actualExpressionValue,
                       const V& toleranceExpressionValue,
                       const TCHAR* fileName, int lineNumber,
                       const TCHAR* message, ...)
{
    if ( expectedExpressionValue < actualExpressionValue )
    {
      if ( (actualExpressionValue - expectedExpressionValue) < toleranceExpressionValue ) return;
    }
    else
    {
      if ( (expectedExpressionValue - actualExpressionValue) < toleranceExpressionValue ) return;
    }

    TCHAR buffer1[MAX_EXPRESSION_STRING] = _T("");
    TCHAR buffer2[MAX_EXPRESSION_STRING] = _T("");
    TCHAR buffer3[MAX_EXPRESSION_STRING] = _T("");

    WinUnit::AssertExceptionT exception;
    exception.AppendMessage(_T("%s(%d): error : WIN_ASSERT_EQUAL_TOL failed. Expected: <%s> (\"%s\"); Actual: <%s> (\"%s\"). Within: <%s>"), 
        fileName,
        lineNumber,
        WinUnit::ToString(expectedExpressionValue, buffer1, ARRAYSIZE(buffer1)),
        expectedExpressionString,
        WinUnit::ToString(actualExpressionValue, buffer2, ARRAYSIZE(buffer2)),
        actualExpressionString,
        WinUnit::ToString(toleranceExpressionValue, buffer3, ARRAYSIZE(buffer3))
        );

    if (message)
    {
        va_list args;
        va_start(args, message);
        exception.AppendMessage(message, args);
        va_end(args);
    }

    throw exception;
}

#pragma warning ( default: 4624 )
