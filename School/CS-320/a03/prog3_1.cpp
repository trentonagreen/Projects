
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Assignment #3-1, Trenton Green, trenton.green@sbcglobal.net" << endl;

    string filename = argv[1];
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, filename.c_str());
}

