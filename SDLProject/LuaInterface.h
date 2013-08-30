#pragma once
#include <string>
#include <stdarg.h>
#include "lua/lua.hpp"

class LuaInterface
{
private:
	lua_State *lua;
	LuaInterface(void);
public:
	~LuaInterface(void);
	void call_function(std::string func, std::string fmt, ...);
	static LuaInterface &get();
};