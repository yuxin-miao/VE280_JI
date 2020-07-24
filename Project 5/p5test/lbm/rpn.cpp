#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

class Mismatch{};
class No_operands{};
class Divide_zero{};
class Over_operands{};

template<class T>
class Stack {
    Dlist<T> list;

public:
    Stack(): list(){};
    // Constructor

    ~Stack() = default;
    // Destructor

    void push(T* val)
    // MODIFIES: this
    // EFFECTS: push val on the top of the stack
    {
        list.insertFront(val);
    }

    T* pop()
    // MODIFIES: this
    // EFFECTS: remove the top of the stack, return the val
    {
        T* val = list.removeFront();
        return val;
    }

    T* top()
    // EFFECTS: return the top of the stack
    {
        T* val = list.removeFront();
        list.insertFront(val);
        return val;
    }

    bool empty() const {return list.isEmpty();}
    // EFFECTS: return true if the list is empty
};

string shunting(const string &str);
    // EFFECTS: generate the RPN algorithem

int compute(const string &rpn);
    // EFFECTS: compute the RPN algorithem

int main(){
    string input;
    getline(cin, input);
    string rpn;
    try {
        rpn = shunting(input);
        cout << rpn << endl;
    }
    catch (Mismatch) {
        cout << "ERROR: Parenthesis mismatch" << endl;
        return 0;
    }
    try {
        int result = compute(rpn);
        cout << result << endl;
    }
    catch (No_operands) {
        cout << "ERROR: Not enough operands" << endl;
    }
    catch (Divide_zero) {
        cout << "ERROR: Divide by zero" << endl;
    }
    catch (Over_operands) {
        cout << "ERROR: Too many operands" << endl;
    }
    return 0;
}

string shunting(const string &str){
    Stack<char> stack;
    string output;
    stringstream input;
    input << str;
    string token;
    while(input >> token){
        if (isdigit(token[0])) { // if the token is a digit
            if (output.empty()){
                output += token; // the first output has no space
            } else {
                output += " ";
                output += token;
            }
        }
        else if (token == "*" || token == "/"|| token == "+" || token == "-"){
            while(!stack.empty()){ // there is ope at the top of the stack
                char *top = stack.pop();
                if ((*top == '(') ||
                    ((*top == '+' || *top == '-') && (token == "*" || token == "/"))){
                    // if the top element is left parenthesis
                    // or the token element has higher precedence
                    stack.push(top);
                    break;
                } else {
                    output += " ";
                    output += *top;
                    delete top;
                }
            }
            stack.push(new char(token[0]));
        }
        else if (token == "("){
            stack.push(new char(token[0]));
        }
        else if (token == ")"){
            while(!stack.empty()){
                char *top = stack.pop();
                if (*top == '(') {
                    stack.push(top);
                    break;
                } else {
                    output += " ";
                    output += *top;
                    delete top;
                }
            }
            if (stack.empty()) throw Mismatch{}; // stack runs out to find a left parenthesis
            char *top = stack.pop();
            if (*top == '(') delete top;
            else stack.push(top);
        }
    }
    while(!stack.empty()){
        char *top = stack.pop();
        if (*top == '(' || *top == ')') {
            delete top;
            throw Mismatch{};
        }
        output += " ";
        output += *top;
        delete top;
    }
    return output;
}

int compute(const string &rpn){
    Stack<int> stack;
    stringstream equation;
    equation << rpn;
    string token;
    while(equation >> token){
        if (isdigit(token[0])){
            stack.push(new int(stoi(token)));
        } else { // if an operator is found
            if (stack.empty()) throw No_operands{};
            int *a = stack.pop();
            if (stack.empty()) { // if only one element in the stack
                delete a;
                throw No_operands{};
            }
            int *b = stack.pop();
            if (token == "*"){
                stack.push(new int((*a) * (*b)));
                delete a;
                delete b;
            }
            else if (token == "/"){
                if (*a == 0) {
                    delete a;
                    delete b;
                    throw Divide_zero{};
                }
                stack.push(new int((*b) / (*a)));
                delete a;
                delete b;
            }
            else if (token == "+"){
                stack.push(new int((*a) + (*b)));
                delete a;
                delete b;
            }
            else if (token == "-"){
                stack.push(new int((*b) - (*a)));
                delete a;
                delete b;
            } else {
                delete a;
                delete b;
            }
        }
    }
    int *top = stack.pop();
    int result = *top;
    delete top;
    if (!stack.empty()) throw Over_operands{};
    return result;
}
