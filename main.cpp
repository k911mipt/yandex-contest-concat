#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include"test.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;

bool ProcessLine(string line);

void ParseFile(string source_file) {
    ifstream input_stream(source_file);
    string line;
    if (input_stream) {
        while (std::getline(input_stream, line)) {
            if (!ProcessLine(line)) {
                cout << line << endl;
            }
        }
    }
}

bool ProcessLine(string line) {
    std::regex re("#include *?\"(.*?)\"");
    std::smatch match;
    if (std::regex_match(line, match, re)) {
        const std::string file_name = match[1];
        cout << endl << "// BEGIN INCLUDING " << file_name << endl;
        ParseFile(file_name);
        cout << "// END INCLUDING " << file_name << endl << endl;
        return true;
    }

    re = std::regex("#pragma once");
    if (std::regex_match(line, match, re)) {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
#ifndef DEBUG
    if (argc <= 2) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return EXIT_SUCCESS;
    }
    string in_file(argv[1]);
    string out_file(argv[2]);
#else
    string in_file("test.cpp");
    string out_file("out.cpp");
#endif // !DEBUG
    cout << "input: " << in_file << endl;
    cout << "output: " << out_file << endl;
    ofstream output_stream(out_file);
    cout.rdbuf(output_stream.rdbuf());
    ParseFile(in_file);
}