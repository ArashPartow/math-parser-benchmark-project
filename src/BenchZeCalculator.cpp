#include "include/BenchZeCalculator.h"

#include "zecalculator/zecalculator.h"

//-------------------------------------------------------------------------------------------------
BenchZeCalculator::BenchZeCalculator()
: Benchmark()
{
   m_sName = "zecalculator v0.4.0";
}

using namespace zc;

//-------------------------------------------------------------------------------------------------
double BenchZeCalculator::DoBenchmark(const std::string& sExpr, long iCount)
{
    ast::MathWorld mathworld;

    GlobalConstant& a = mathworld.add<GlobalConstant>("a", 1.1).value();
    GlobalConstant& b = mathworld.add<GlobalConstant>("b", 2.2).value();
    GlobalConstant& x = mathworld.add<GlobalConstant>("x", 2.123456).value();
    GlobalConstant& y = mathworld.add<GlobalConstant>("y", 3.123456).value();

    mathworld.add<GlobalConstant>("c", 3.3).value();
    mathworld.add<GlobalConstant>("y", 4.123456).value();
    mathworld.add<GlobalConstant>("w", 4.123456).value();

    ast::Expression& expr = mathworld.add<ast::Expression>("expr", sExpr).value();

    double fSum = 0;

    if (not std::holds_alternative<Ok>(expr.parsing_status()))
    {
        StopTimerAndReport("parsing failure");
        return std::numeric_limits<double>::quiet_NaN();
    }

    double fRes = expr().value();

    StartTimer();

    for (int j = 0; j < iCount; ++j)
    {
        fSum += expr().value();
        std::swap(a.value, b.value);
        std::swap(x.value, y.value);
    }

    StopTimer(fRes, fSum, iCount);

    return m_fTime1;
}

//-------------------------------------------------------------------------------------------------
std::string BenchZeCalculator::GetShortName() const
{
   return "zecalculator";
}
