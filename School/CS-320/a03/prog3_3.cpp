#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>


extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Assignment #3-3, Trenton Green, trenton.green@sbcglobal.net" << endl;

    string file = argv[1];
    char buff[256];
    
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, file.c_str()); 
    fgets(buff, 65, stdin);

    lua_getglobal(L, "InfixToPostfix");
    lua_pushstring(L, buff);
    lua_call(L, 1, 1);

    luaL_checkstring(L, 1);
    string postfix = lua_tostring(L, -1);
    lua_pop(L, 1);

    cout << postfix + "\n";

    lua_close(L);
}