#include "LuaInterface.h"
#include "Log.h"
LuaInterface::LuaInterface(void)
{
	this->lua = luaL_newstate();
}


LuaInterface::~LuaInterface(void)
{
	delete this->lua;
}

void LuaInterface::call_function(std::string func, std::string fmt, ...) {
	va_list list;
	va_start(list, fmt);
	int i = 0;
	lua_getglobal(this->lua, func.c_str());
	while(i < fmt.size()) {
		switch(fmt[i]) {
		case 'd':
			lua_pushnumber(this->lua, va_arg(list, double));
			break;
		case 'i':
			lua_pushnumber(this->lua, va_arg(list, int));
			break;
		case 's':
			lua_pushstring(this->lua, va_arg(list, char*));
			break;
		case '>':
			goto next;
		default:
			Log::Errorf("Invalid specifier: %c", fmt[i]);
		}
		i++;
	}
next:
	i++;
	while(i < fmt.size()) {
	}
	
	va_end(list);
}

LuaInterface &LuaInterface::get() {
	static LuaInterface inst;
	return inst;
}