#include "prog2_1.hpp"
#include "prog2_3.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    cout <<"Assignment #2-4, Trenton Green, trenton.green@sbcglobal.net"<< endl;

    if(argc != 2) {
        printf("\nThis program expects a single command line argument.\n");
        return 0;
    } 
    
    Parser *pars = new Parser();
    Tokenizer *token = new Tokenizer();

    ifstream file (argv[1]);
    int j = 0;
    bool hasError = false;
    vector<string> svec;
    
    while(!file.eof()) {  
        Tokenizer *toke = new Tokenizer();

        string s;
        getline(file, s);
        vector<string> vec;
        toke->Tokenize(s);
        token->Tokenize(s);
        j++;
        
        for(int x = 0; x < toke->data->size(); x++) {
            vec.push_back(toke->data->at(x));
        }

        if(toke->garbagecontainer.size() > 0) {
            cout << "Error on line " << j << ": Unexpected token: " << toke->garbagecontainer.at(0) << endl;
            hasError = true;
            break;        
        }

        if(!pars->Parse(vec)) {
            if(vec.size() == 1)
                cout << "Parse error on line " << j << ": " << vec.at(0) << endl; 
            if(vec.size() == 2)
                cout << "Parse error on line " << j << ": " << vec.at(0) << " " << vec.at(1) << endl; 
            hasError = true; 
            break;
        }

        toke->~Tokenizer();
        vec.clear();
    }
    if(!hasError)
        token->GetTokens();
    pars->~Parser();
    token->~Tokenizer();
}
