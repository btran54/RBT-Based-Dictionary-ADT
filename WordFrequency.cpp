/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA8
* WordFrequency.cpp
* WordFrequency CPP file that will operate Dictionary CPP functions on provided txt files
***/

#include <iostream>
#include <fstream>
#include <string>

#include "Dictionary.h"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cerr << "Invalid Argument.\nUsage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    ifstream in;
    ofstream out;
    in.open(argv[1]);
    out.open(argv[2]);

    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return 1;
    }

    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return 1;
    }

    Dictionary wordFrq;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    string line;
    size_t begin, end, wordLen;
    string TB;
    string token;

    int frq = 1;

    while (getline(in, line)) {
      wordLen = line.length();
      begin = min(line.find_first_not_of(delim, 0), wordLen);
      end   = min(line.find_first_of(delim, begin), wordLen);
      token = line.substr(begin, end-begin);

      while (token != "") {
        int tokSize = token.length();

        for (int i = 0; i < tokSize; i++) {
           token[i] = tolower(token[i]);
        }

        if (!wordFrq.contains(token)) {
            frq = 1;
            wordFrq.setValue(token, frq);
        } 
        
        else {
            wordFrq.getValue(token)++;
        }

        begin = min(line.find_first_not_of(delim, end+1), wordLen);
        end   = min(line.find_first_of(delim, begin), wordLen);
        token = line.substr(begin, end-begin);
      }
    }

    out << wordFrq;
    in.close();
    out.close();
    return 0;
}