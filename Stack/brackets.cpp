#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>

bool isValid(const std::string& s);

bool isValid(const std::string& s) 
{
    std::stack<char> myStack;
    for (int i = 0; i < s.size(); i++) 
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') 
            myStack.push(s[i]);
        else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
        {
            if (myStack.empty()) 
                return false;
            if (s[i] == ')' && myStack.top() != '(') 
                return false;
            if (s[i] == ']' && myStack.top() != '[') 
                return false;
            if (s[i] == '}' && myStack.top() != '{') 
                return false;
            myStack.pop();
        }
        else
        {
            std::cerr << "Invalid character: " << s[i] << std::endl;
            exit(-1);
        }
    }
    return myStack.empty();
}    

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " <string>" << std::endl;
        return -1;
    }
    if (isValid(argv[1]))
        std::cout << "Valid" << std::endl;
    else
        std::cout << "Invalid" << std::endl;
    return 0;    
};