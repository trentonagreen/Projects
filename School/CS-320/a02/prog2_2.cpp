#include "prog2_1.hpp"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    cout <<"Assignment #2-2, Trenton Green, trenton.green@sbcglobal.net"<< endl;
    
    if(argc != 2) {
        printf("\nThis program expects a single command line argument.\n");
        return 0;
    } 

    Tokenizer *toke = new Tokenizer();

    ifstream file (argv[1]);
    int j = 0;
    int i = 0;

    while(!file.eof()) {
        string s;
        getline(file, s);
        toke->Tokenize(s);
        j++;

        if(toke->garbagecontainer.size() > 0) {
            cout << "Error on line " << j << ": Unexpected token: " << toke->garbagecontainer.at(0) << endl;
            break;        
        }

        i++;
    } 
    toke->GetTokens();
    toke->~Tokenizer();
}


