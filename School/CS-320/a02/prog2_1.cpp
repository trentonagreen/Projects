#include "prog2_1.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ctype.h>

using namespace std;

Tokenizer::Tokenizer() {
    this->data = new vector<string>();
}

Tokenizer::~Tokenizer() {
    delete this->data;
}

void Tokenizer::Tokenize(string tokenize) {

    stringstream ss(tokenize);
    while(!ss.eof()) {
        string s;
        ss >> s;
        svec.push_back(s);
        data->push_back(s);
    }
    for(int i = 0; i < svec.size() ; i++) {

        if(svec.at(i) == "push") { 
            scontainer.push_back(svec.at(i));  
        }
        else if(svec.at(i) == "pop") {
            scontainer.push_back(svec.at(i));   
        }
        else if(svec.at(i) == "add") {
            scontainer.push_back(svec.at(i)); 
        }
        else if(svec.at(i) == "sub") {
            scontainer.push_back(svec.at(i)); 
        }
        else if(svec.at(i) == "mul") {
            scontainer.push_back(svec.at(i));   
        }
        else if(svec.at(i) == "pop") {
            scontainer.push_back(svec.at(i));   
        }
        else if(svec.at(i) == "skip") {
            scontainer.push_back(svec.at(i));     
        } 
        else if(svec.at(i) == "save") { 
            scontainer.push_back(svec.at(i)); 
        }
        else if(svec.at(i) == "get") { 
            scontainer.push_back(svec.at(i));
        }
        else if(svec.at(i) == "div") { 
            scontainer.push_back(svec.at(i));
        }
        else if(svec.at(i) == "mod") { 
            scontainer.push_back(svec.at(i));
        }
        else if(tokenize.empty()) {
            continue;
        }
        else {
            if(isNumber(svec.at(i))) {
                scontainer.push_back(svec.at(i));
                break;        
            }         
            else {
                garbagecontainer.push_back(svec.at(i));
            }
        }
    }
    svec.clear();
}

vector<string> Tokenizer::GetTokens() {
    if(scontainer.size() == 0) {
        cout << "No tokens" << endl;
        return scontainer;
    }
    if(garbagecontainer.size() > 0) {
        return garbagecontainer;
    }
    for(int i = 0; i < scontainer.size(); i++) {
        if(scontainer.at(i) == "push" || scontainer.at(i) == "save" || scontainer.at(i) == "get") {
            cout << scontainer.at(i) << ",";
        }
        else if(scontainer.at(i).empty())
            continue;
        else
            cout << scontainer.at(i) << endl;
        //else
            //cout << scontainer.at(i) << " " << endl;
    }
    return scontainer;
}

bool Tokenizer::isNumber(string s) {
    for(int i = 0; i < s.length(); i++) {
        if(isdigit(s[i]) == false) {
            return false;
        }
    }
    return true;
}
