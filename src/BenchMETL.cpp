#include "BenchMETL.h"

#include <cmath>

#include "METL/metl.h"

//-------------------------------------------------------------------------------------------------
BenchMETL::BenchMETL()
	: Benchmark()
{
	m_sName = "METL";
}

//-------------------------------------------------------------------------------------------------
double BenchMETL::DoBenchmark(const std::string& sExpr, long iCount)
{
	auto compiler = metl::makeCompiler<int, double>();
	metl::setDefaults(compiler); // add default operators and functions for ints and doubles.

	// required because metl would otherwise do int-division
	compiler.setOperator<int, int>("/", [](const auto& left, const auto& right)
	{
		return double(left) / right;
	});

	// metl-defaults do not provide operator<, especially not such that it returns double
	compiler.setOperator<double, double>("<", [](double left, double right) -> double
	{
		return static_cast<double>(left < right);
	});

	// a little optimization
	compiler.setFunction<double>("e^", [](double exponent) ->double
	{
		return std::exp(exponent);
	});

	double a = 1.1;
	double b = 2.2;
	double c = 3.3;
	double x = 2.123456;
	double y = 3.123456;
	double z = 4.123456;
	double w = 5.123456;

	compiler.setVariable("a", &a);
	compiler.setVariable("b", &b);
	compiler.setVariable("c", &c);
	compiler.setVariable("x", &x);
	compiler.setVariable("y", &y);
	compiler.setVariable("z", &z);
	compiler.setVariable("w", &w);

	// copied from exprtk::numeric::constant
	const auto e = 2.71828182845904523536028747135266249775724709369996;
	const auto pi = 3.14159265358979323846264338327950288419716939937510;

	compiler.setConstant("e", e);
	compiler.setConstant("pi", pi);

	// Perform basic tests for the variables used
	// in the expressions
	{
		bool test_result = true;

		auto tests_list = test_expressions();

		for (auto test : tests_list)
		{
			try
			{
				auto f = compiler.build<double>(test.first);
				test_result = (f() == test.second);
			}
			catch (const std::runtime_error&)
			{
				test_result = false;
			}

			if (!test_result) break;
		}

		if (!test_result)
		{
			StopTimerAndReport("Failed variable test");
			return m_fTime1;
		}
	}


	std::function<double()> f;
	{
		try
		{
			f = compiler.build<double>(sExpr);
		}
		catch (const std::runtime_error& error)
		{
			StopTimerAndReport(error.what());
			return m_fTime1;
		}
	}

	//Prime the I and D caches for the expression. 
	{
		double d0 = 0.0;
		double d1 = 0.0;

		for (std::size_t i = 0; i < priming_rounds; ++i)
		{
			if (i & 1)
				d0 += f();
			else
				d1 += f();
		}

		if (
			(d0 == std::numeric_limits<double>::infinity()) &&
			(d1 == std::numeric_limits<double>::infinity())
			)
		{
			printf("\n");
		}
	}


	// Perform benchmark then return results
	double fRes = 0;
	double fSum = 0;

	fRes = f();

	StartTimer();

	for (int j = 0; j < iCount; ++j)
	{
		fSum += f();
		std::swap(a, b);
		std::swap(x, y);
	}

	StopTimer(fRes, fSum, iCount);

	return m_fTime1;
}
