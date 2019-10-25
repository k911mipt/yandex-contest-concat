#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_set>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::regex;
using std::regex_match;

enum LineAction : bool {
    SKIP_LINE,
    WRITE_LINE
};

LineAction ProcessLine(const string& line);

void ParseFile(const string& source_file) {
    ifstream input_stream(source_file);
    string line;
    if (input_stream) {
        while (std::getline(input_stream, line)) {
            if (ProcessLine(line) == WRITE_LINE) {
                cout << line << endl;
            }
        }
    }
}

const regex re_include_local_filename("#include[[:space:]]*?\"(.*?)\"\r?");
const regex re_include_global_filename("#include[[:space:]]*?<(.*?)>\r?");
const regex re_pragma_once("#pragma once\r?");
std::unordered_set<string> included_local_files;
std::unordered_set<string> included_global_files;

LineAction ProcessLine(const string& line) {
    std::smatch match;
    // Check including local files
    if (regex_match(line, match, re_include_local_filename)) {
        const std::string file_name = match[1];
        if (included_local_files.insert(file_name).second) {
            cout << endl << "// BEGIN INCLUDING " << file_name << endl;
            ParseFile(file_name);
            cout << "// END INCLUDING " << file_name << endl << endl;
        }
        return SKIP_LINE;
    }
    // Check including global file
    if (regex_match(line, match, re_include_global_filename)) {
        const std::string file_name = match[1];
        if (included_global_files.insert(file_name).second) {
            return WRITE_LINE;
        }
        return SKIP_LINE;
    }
    // skip windows #pragma once
    if (regex_match(line, match, re_pragma_once)) {
        return SKIP_LINE;
    }
    return WRITE_LINE;
}

int main(int argc, char** argv) {
#ifndef DEBUG
    if (argc <= 2) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
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