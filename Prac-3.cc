#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <regex>

using namespace std;

// C keywords
set<string> keywords = {
    "int", "char", "float", "double", "if", "else",
    "while", "for", "return", "void", "break", "continue"
};

// Operators and punctuations
set<string> operators = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">="};
set<char> punctuations = {';', ',', '(', ')', '{', '}', '[', ']'};

set<string> symbolTable;
vector<string> lexicalErrors;

// Remove comments
string removeComments(string code) {
    regex singleLine("//.*");
    regex multiLine("/\\*[\\s\\S]*?\\*/");

    code = regex_replace(code, singleLine, "");
    code = regex_replace(code, multiLine, "");

    return code;
}

bool isNumber(string s) {
    return regex_match(s, regex("[0-9]+"));
}

bool isCharConst(string s) {
    return regex_match(s, regex("\'.\'"));
}

bool isIdentifier(string s) {
    return regex_match(s, regex("[a-zA-Z_][a-zA-Z0-9_]*"));
}

int main() {
    string filename;
    cout << "Enter C source file name: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Unable to open file\n";
        return 0;
    }

    string code, line;
    while (getline(file, line)) {
        code += line + "\n";
    }
    file.close();

    code = removeComments(code);

    stringstream ss(code);
    string token;
    int lineNo = 1;

    cout << "\nTOKENS\n";

    while (getline(ss, line)) {
        string temp;
        for (int i = 0; i < line.length(); i++) {
            char ch = line[i];

            if (isspace(ch)) continue;

            // Punctuation
            if (punctuations.count(ch)) {
                cout << "Punctuation: " << ch << endl;
            }

            // Operator
            else if (operators.count(string(1, ch))) {
                cout << "Operator: " << ch << endl;
            }

            // Identifier / Keyword / Constant
            else if (isalnum(ch) || ch == '_' || ch == '\'') {
                temp = "";
                while (i < line.length() &&
                      (isalnum(line[i]) || line[i] == '_' || line[i] == '\'')) {
                    temp += line[i++];
                }
                i--;

                if (keywords.count(temp)) {
                    cout << "Keyword: " << temp << endl;
                }
                else if (isNumber(temp)) {
                    cout << "Constant: " << temp << endl;
                }
                else if (isCharConst(temp)) {
                    cout << "Constant: " << temp << endl;
                }
                else if (isIdentifier(temp)) {
                    cout << "Identifier: " << temp << endl;
                    symbolTable.insert(temp);
                }
                else {
                    lexicalErrors.push_back("Line " + to_string(lineNo) + ": " + temp + " invalid lexeme");
                }
            }
        }
        lineNo++;
    }

    cout << "\nLEXICAL ERRORS\n";
    if (lexicalErrors.empty()) {
        cout << "None\n";
    } else {
        for (auto err : lexicalErrors)
            cout << err << endl;
    }

    cout << "\nSYMBOL TABLE ENTRIES\n";
    int index = 1;
    for (auto sym : symbolTable) {
        cout << index++ << ") " << sym << endl;
    }

    return 0;
}
