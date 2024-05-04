#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

bool isKeyword(const string& token)
{
    static unordered_set<string> keywords = {"int", "float", "double", "char", "if", "else", "for", "while", "do", "return", "cin", "cout", "endl"};
    return keywords.find(token) != keywords.end();
}

bool isValidIdentifier(const string& token)
{
    if (!isalpha(token[0]) && token[0] != '_')
        return false;
    for (char c : token)
        {
        if (!isalnum(c) && c != '_')
            return false;
    }
    return true;
}

bool isNumber(const string& token) {
    for (char c : token)
        {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main() {
    string input = R"(
        #include <iostream>
        using namespace std;

        int main() {
            cout << "Welcome";
            int x = 24 % 10;
            if (x == 4) {
                x = 40;
            }
            int y = 50;
            int #z = 60;
            return 0;
        }
    )";

    stringstream ss(input);
    string token;
    vector<string> tokens;

    while (ss >> token) {

        if (token == "#include") {
            tokens.push_back("Predefined name: " + token);
            ss >> token;
            tokens.push_back("Header file: " + token);
        }
        else if (token == "using") {
            tokens.push_back("Namespace declaration: " + token);
            ss >> token;
            tokens.push_back(token);
            ss >> token;
            tokens.push_back(token);
        }
         else if (isKeyword(token)) {
            tokens.push_back("Built-in keyword: " + token);
        }
        else if (isValidIdentifier(token)) {
            tokens.push_back("Predefined name: " + token);
        }
        else if (isNumber(token)) {
            tokens.push_back("Constant: " + token);
        }
        else
            {
            tokens.push_back("Invalid data type or token: " + token);
        }
    }


    for (const string& token : tokens)
    {
        cout << token << endl;
    }

    return 0;
}
