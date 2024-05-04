/***
* Brian Tran
* btran54
* 2024 Winter CSE101 PA8
* Order.cpp
* Order CPP file containing the main execution of Dictionary.cpp functions
***/

#include <iostream>
#include <fstream>
#include <string>

#include "Dictionary.h"

using namespace std;

int main (int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Invalid Arguments.\nUsage: " << argv[0] << "<input file> <output file>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    ofstream out(argv[2]);

    if (!in) {
        cerr << "Failed to open file " << argv[1] << " for reading.\n" << endl;
        return 1;
    }

    if (!out) {
        cerr << "Failed to open file " << argv[2] << " for writing.\n" << endl;
        return 1;
    }

    Dictionary dict;
    string line;
    int lineNum = 1;

    while (getline(in, line)) {
        dict.setValue(line, lineNum);
        lineNum++;
    }

    out << dict << endl;
    out << dict.pre_string();
    out << endl;

    in.close();
    out.close();

    return 0;
}