#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <cctype>
using namespace std;

// Check if string is number
bool isNumber(string s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Apply operation
string applyOp(string a, string b, string op) {
    double x = stod(a);
    double y = stod(b);
    double res;

    if (op == "+") res = x + y;
    else if (op == "-") res = x - y;
    else if (op == "*") res = x * y;
    else if (op == "/") res = x / y;

    // remove trailing zeros
    ostringstream out;
    out << res;
    return out.str();
}

// Infix → Postfix
vector<string> infixToPostfix(string expr) {
    stack<char> st;
    vector<string> output;

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;

        // number or variable
        if (isalnum(expr[i])) {
            string token;
            while (i < expr.length() && (isalnum(expr[i]) || expr[i]=='.')) {
                token += expr[i];
                i++;
            }
            i--;
            output.push_back(token);
        }
        else if (expr[i] == '(') {
            st.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() && precedence(st.top()) >= precedence(expr[i])) {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            st.push(expr[i]);
        }
    }

    while (!st.empty()) {
        output.push_back(string(1, st.top()));
        st.pop();
    }

    return output;
}

// Constant Folding
string constantFolding(vector<string> postfix) {
    stack<string> st;

    for (string token : postfix) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();

            // If both are numbers → evaluate
            if (isNumber(a) && isNumber(b)) {
                string res = applyOp(a, b, token);
                st.push(res);
            } else {
                // Keep expression as string
                string expr = a + " " + token + " " + b;
                st.push(expr);
            }
        } else {
            st.push(token);
        }
    }

    return st.top();
}

int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);

    vector<string> postfix = infixToPostfix(expr);
    string optimized = constantFolding(postfix);

    cout << "\nOptimized Expression: " << optimized << endl;

    return 0;
}