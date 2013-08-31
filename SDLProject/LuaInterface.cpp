#include "LuaInterface.h"
#include "Log.h"
LuaInterface::LuaInterface(void)
{
	this->lua = luaL_newstate();
	luaL_openlibs(this->lua);
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
			lua_pushstring(this->lua, va_arg(list, char *));
			break;
		case '>':
			goto next;
		default:
			Log::Errorf("Invalid arg specifier: %c", fmt[i]);
			va_end(list);
			return;
		}
		i++;
	}
next:
	i++;
	int numresults = fmt.size() - i;
	Log::Infof("%d %d", i-1, numresults);
	if(lua_pcall(this->lua, i-1, numresults, 0) != 0) {
		Log::Errorf("Error calling lua function %s: %s", func.c_str(), lua_tostring(this->lua, -1));
		return;
	}
	while(i < fmt.size()) {
		switch(fmt[i]) {
		case 'd':
			*va_arg(list, double *) = lua_tonumber(this->lua, -numresults);
			break;
		case 'i':
			*va_arg(list, int *) = (int)lua_tonumber(this->lua, -numresults);
			break;
		case 's':
			*va_arg(list, const char**) = lua_tostring(this->lua, -numresults);
			break;
		default:
			Log::Errorf("Invalid result specifier: %c", fmt[i]);
			va_end(list);
			return;
		}
		i++;
		numresults--;
	}
	
	va_end(list);
}

LuaInterface &LuaInterface::get() {
	static LuaInterface inst;
	return inst;
}

void LuaInterface::load_file(std::string filename) {
	if(luaL_loadfile(this->lua, filename.c_str())) {
		Log::Errorf("Lua file failed to load: %s", lua_tostring(lua, -1));
	}
	lua_pcall(lua, 0, 0, 0);
}