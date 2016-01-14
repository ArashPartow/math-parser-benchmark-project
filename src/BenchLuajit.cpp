#include "BenchLuaJit.h"
#include <cstdio>
#include <map>
#include <lua.hpp>

//-------------------------------------------------------------------------------------------------
BenchLuaJit::BenchLuaJit()
	: Benchmark()
{
	m_sName = "LuaJit";
}

void ErrorPrint(lua_State* L, int retVal)
{
	if (retVal == 0)
	{
		return;
	}

	printf("%s\n", lua_tostring(L, -1));
	lua_pop(L, 1);
}

//-------------------------------------------------------------------------------------------------
double BenchLuaJit::DoBenchmark(const std::string& sExpr, long iCount)
{	
	std::map<std::string, double> var_list;
	var_list["a"] = 1.1;
	var_list["b"] = 2.2;
	var_list["c"] = 3.3;
	var_list["x"] = 2.123456;
	var_list["y"] = 3.123456;
	var_list["z"] = 4.123456;
	var_list["w"] = 5.123456;

	var_list["e"] = 2.718281828459045235360;
	var_list["pi"] = 3.141592653589793238462;

	lua_State *L;
	try
	{		
		L = luaL_newstate();
				
		for (auto it = var_list.begin(); it != var_list.end(); ++it)
		{
			lua_pushnumber(L, it->second);
			lua_setglobal(L, it->first.c_str());
		}		

		int result = luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE);
		ErrorPrint(L, luaL_dostring(L, ("function fnkt() return " + sExpr + "; end").c_str()));
		ErrorPrint(L, luaL_dostring(L, 
			("function fnktWithSwap() local result = " + sExpr + 
			"  a,b = b,a; x,y = y,x; "
			"  return result; "
			"end").c_str()));
	}
	catch (std::exception& e)
	{
		StopTimerAndReport(e.what());
		return std::numeric_limits<double>::quiet_NaN();
	}

	// Calculate/bench and show result finally
	double fRes = 0;
	double fSum = 0;

	lua_getglobal(L, "fnkt");
	lua_pcall(L, 0, 1, 0);
	fRes = lua_tonumber(L, -1);
	lua_pop(L, 1);

	StartTimer();

	for (int j = 0; j < iCount; ++j)
	{
		lua_getglobal(L, "fnktWithSwap");
		lua_pcall(L, 0, 1, 0);
		double result = lua_tonumber(L, -1);
		fSum += result;
		lua_pop(L, 1);
	}

	StopTimer(fRes, fSum, iCount);
	lua_close(L);
	return m_fTime1;
}
