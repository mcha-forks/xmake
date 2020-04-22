#include <xmake/xmake.h>

static tb_int_t lni_test_hello(lua_State* lua)
{
    lua_pushliteral(lua, "hello xmake!");
    return 1;
}
static tb_void_t lni_initalizer(xm_engine_ref_t engine, lua_State* lua)
{
    static luaL_Reg const lni_test_funcs[] = 
    {
        {"hello", lni_test_hello}
    ,   {tb_null, tb_null}
    };
    xm_engine_register(engine, "test", lni_test_funcs);
}
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
    tb_int_t ok = -1;
    if (xm_init())
    {
        xm_engine_ref_t engine = xm_engine_init(lni_initalizer);
        if (engine)
        {
#if 0
            tb_int_t   argc2 = argc + 2;
            tb_char_t* argv2[argc2 + 1];
            argv2[0]  = argv[0];
            argv2[1]  = "lua";
            argv2[2]  = "lua.main";
            if (argc > 1) tb_memcpy(argv2 + 3, argv + 1, (argc - 1) * sizeof(tb_char_t*));
            argv2[argc2] = tb_null;
#else
            tb_int_t   argc2 = argc + 3;
            tb_char_t* argv2[argc2 + 1];
            argv2[0]  = argv[0];
            argv2[1]  = "lua";
            argv2[2]  = "-vD";
            argv2[3]  = "lua.main";
            if (argc > 1) tb_memcpy(argv2 + 4, argv + 1, (argc - 1) * sizeof(tb_char_t*));
            argv2[argc2] = tb_null;
#endif
            ok = xm_engine_main(engine, argc2, argv2);
            xm_engine_exit(engine);
        }
        xm_exit();
    }
    return ok;
}
