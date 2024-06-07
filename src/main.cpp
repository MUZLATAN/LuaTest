#include "iostream"
extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

/*
    Lua���쳣������Ҫ����pcall��xpcall������
*/

void getStackSize(const char* desc, const int count)
{
    printf("%s stack size = [ %d ]\n", desc, count);
}

void test_api_getfield()
{
    lua_State* L = luaL_newstate();

    // ���ز�ִ��Ŀ��lua�ļ�
    if (LUA_OK != luaL_dofile(L, ".\\script.lua")) {
        const char* err = lua_tostring(L, -1);
        fprintf(stderr, "err:\t%s\n", err);
        return;
    }

    lua_getglobal(L, "tab");           // ���� tab ����ѹ��ջ��

    // lua_gettop ��ȡջ��Ԫ������
    getStackSize("stage 1", lua_gettop(L));

    // 
    lua_getfield(L, -1, "a");           // �� tab.a ��ջ
    int nTab_a = lua_tointeger(L, -1); // �� tab.a ȡ����ֵ������nTab_a

    lua_getfield(L, -2, "b");           // �� tab.b ��ջ
    int nTab_b = lua_tointeger(L, -1); // �� tab.b ȡ����ֵ������nTab_b
    getStackSize("stage 2", lua_gettop(L));

    lua_pop(L, 3);                  // �����ջ�ж����3������tab��tab.a��tab.b
    getStackSize("stage 3", lua_gettop(L));

    int nTab_c = 2 * nTab_a + nTab_b;
    lua_pushinteger(L, nTab_c);       // �� c = 2a + b ������ɣ�ѹ��ջ��
    printf("nTab_c = %d \n", nTab_c);  // ����� 5

    getStackSize("stage 4", lua_gettop(L));

    lua_getglobal(L, "lua_func");        // ����lua_func����������ѹ��ջ��
    lua_pushinteger(L, 3);              // ѹ�뺯������ x=3  
    getStackSize("stage 5", lua_gettop(L));

    // lua_pcall �ڱ���ģʽ�µ���һ������,��ֹ�쳣����ֱ���˳�
    lua_pcall(L, 1, 1, 0);             // ִ�нű�����lua_func

    getStackSize("stage 6", lua_gettop(L));

    int result = lua_tointeger(L, -1);   // ��ջ��ȡ�ط���ֵ 
    getStackSize("stage 7", lua_gettop(L));
    printf("res = %d \n", result);


    lua_pop(L, 1);                       // �������ؽ��
    getStackSize("stage 8", lua_gettop(L));

    lua_close(L);                       //�ر�lua����  
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
