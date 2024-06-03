extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

class LuaObject
{

public:
	lua_State* L;

public:
	bool initLua();
	bool CallLuaFunc();
};