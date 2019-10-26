#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_set>

using std::string;
using std::cout;
using std::endl;
using std::regex_match;

enum LineAction {
    SKIP_LINE,
    WRITE_LINE,
    PASS
};

LineAction ProcessLine(const string& line);

void ParseFile(const string& source_file) {
    std::ifstream input_stream(source_file);
    string line;
    if (input_stream) {
        while (std::getline(input_stream, line)) {
            if (ProcessLine(line) == WRITE_LINE) {
                cout << line << endl;
            }
        }
    }
}

const std::regex re_include_local_filename("#include[[:space:]]*?\"(.*?)\"\r?");
const std::regex re_include_global_filename("#include[[:space:]]*?<(.*?)>\r?");
const std::regex re_pragma_once("#pragma once\r?");
std::unordered_set<string> included_local_files;
std::unordered_set<string> included_global_files;
string begin_include = "#pragma region ";
string end_include = "#pragma endregion ";
std::smatch match;

LineAction CheckLocalInclude(const string& line) {
    if (regex_match(line, match, re_include_local_filename)) {
        const std::string file_name = match[1];
        if (included_local_files.insert(file_name).second) {
            cout << endl << begin_include << "\"" << file_name << "\"" << endl;
            ParseFile(file_name);
            cout << end_include << "\"" << file_name << "\"" << endl;
        }
        return SKIP_LINE;
    }
    return PASS;
}

LineAction CheckGlobalInclude(const string& line) {
    if (regex_match(line, match, re_include_global_filename)) {
        const std::string file_name = match[1];
        if (included_global_files.insert(file_name).second) {
            return WRITE_LINE;
        }
        return SKIP_LINE;
    }
    return PASS;
}

LineAction CheckPragmaOnce(const string& line) {
    if (regex_match(line, match, re_pragma_once)) {
        return SKIP_LINE;
    }
    return PASS;
}

LineAction ProcessLine(const string& line) {
    LineAction result;
    if ((result = CheckLocalInclude(line)) != PASS)
        return result;
    if ((result = CheckGlobalInclude(line)) != PASS)
        return result;
    if ((result = CheckPragmaOnce(line)) != PASS)
        return result;
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
    std::ofstream output_stream(out_file);
    cout.rdbuf(output_stream.rdbuf());
    ParseFile(in_file);
}