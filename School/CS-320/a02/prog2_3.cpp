#include "prog2_3.hpp"
#include <vector>
#include <string>
#include <iostream>

#include <fstream>

using namespace std;

Parser::Parser() {

}

Parser::~Parser() {

}

bool Parser::Parse(vector<string> vec) {
    if(vec.at(0) == "pop" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0) == "add" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0) == "sub" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0) == "mul" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0) == "div" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0) == "mod" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0) == "skip" && vec.size() == 1) {
        return true;
    }
    else if(vec.at(0).empty() && vec.size() > 0) {
        return true;    
    }
    else if(vec.at(0) == "push" && vec.size() == 2) {
        return true;
    }
    else if(vec.at(0) == "save" && vec.size() == 2) {
        return true;
    }
    else if(vec.at(0) == "get" && vec.size() == 2) {
        return true;
    }
    else if(vec.at(1).empty())  //
        return true;            //
    return false;
}
