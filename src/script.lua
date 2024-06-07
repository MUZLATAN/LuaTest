-- tab 表
tab =
{
    a = 2,
    b = 1
}

-- 全局变量c
c = 100;

function lua_func(x)
    -- print("lua c: ", c)
    return (tab.a * x * x + tab.b * x + c)
end