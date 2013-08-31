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
	void load_file(std::string filename);
	static LuaInterface &get();
};