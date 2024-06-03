#include "lua_manager.h"

bool LuaObject::initLua()
{
	L = luaL_newstate();
	if (L == nullptr)
	{
		return false;
	}



}