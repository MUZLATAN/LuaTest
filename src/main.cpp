#include "iostream"
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

/*
    Lua的异常捕获主要基于pcall及xpcall函数。
*/

void getStackSize(const char* desc, const int count)
{
    printf("%s stack size = [ %d ]\n", desc, count);
}

void test_api_getfield()
{
    lua_State* L = luaL_newstate();

    // 加载并执行目标lua文件
    if (LUA_OK != luaL_dofile(L, ".\\script.lua")) {
        const char* err = lua_tostring(L, -1);
        fprintf(stderr, "err:\t%s\n", err);
        return;
    }

    lua_getglobal(L, "tab");           // 查找 tab 变量压入栈底

    // lua_gettop 获取栈中元素数量
    getStackSize("stage 1", lua_gettop(L));

    // 
    lua_getfield(L, -1, "a");           // 将 tab.a 入栈
    int nTab_a = lua_tointeger(L, -1); // 将 tab.a 取出赋值给变量nTab_a

    lua_getfield(L, -2, "b");           // 将 tab.b 入栈
    int nTab_b = lua_tointeger(L, -1); // 将 tab.b 取出赋值给变量nTab_b
    getStackSize("stage 2", lua_gettop(L));

    lua_pop(L, 3);                  // 清除掉栈中多余的3个变量tab、tab.a、tab.b
    getStackSize("stage 3", lua_gettop(L));

    int nTab_c = 2 * nTab_a + nTab_b;
    lua_pushinteger(L, nTab_c);       // 将 c = 2a + b 计算完成，压入栈顶
    printf("nTab_c = %d \n", nTab_c);  // 输出： 5

    getStackSize("stage 4", lua_gettop(L));

    lua_getglobal(L, "lua_func");        // 查找lua_func函数并将其压入栈底
    lua_pushinteger(L, 3);              // 压入函数变量 x=3  
    getStackSize("stage 5", lua_gettop(L));

    // lua_pcall 在保护模式下调用一个函数,防止异常程序直接退出
    lua_pcall(L, 1, 1, 0);             // 执行脚本函数lua_func

    getStackSize("stage 6", lua_gettop(L));

    int result = lua_tointeger(L, -1);   // 从栈中取回返回值 
    getStackSize("stage 7", lua_gettop(L));
    printf("res = %d \n", result);


    lua_pop(L, 1);                       // 弹出返回结果
    getStackSize("stage 8", lua_gettop(L));

    lua_close(L);                       //关闭lua环境  
}

int main(int argc, char** argv)
{
    lua_State* L;
    /* Create a Lua state */
    L = luaL_newstate();
    /* Check the return value */
    if (L == NULL) {
        fprintf(stderr, "Lua: cannot initialize\n");
        return -1;
    }

    test_api_getfield();
    getchar();
    return 0;
}
