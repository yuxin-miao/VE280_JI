#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "dlist.h"

using namespace std;

template<class T>
class Stack {
    Dlist<T> dlist;
    int n;
public:
    Stack(): dlist(), n(0){};
    // EFFECTS: constructor
    bool empty() {return dlist.isEmpty();}
    // EFFECTS: check whether dlist is empty
    void push(T* val) {dlist.insertFront(val); n++;}
    // MODIFIES: this
    // EFFECTS: push ch on the top of the stack
    T* pop() {T* val = dlist.removeFront(); n--; return val;}
    // MODIFIES: this
    // EFFECTS: pop out the top element of the stack, return the top element
    T* top() {T* val = dlist.removeFront(); dlist.insertFront(val); return val;}
    // EFFECTS: return the top value of the stack
    int size() { return n;}
    // EFFECTS: return the size of the stack
};


string convertInfix(const string& infix);
// EFFECTS: convert an infix expression to an RPN one, and return the RPN expression
int computeRPN(string& rpn);
// EFFECTS: compute value based on the rpn expression, and return the result

int main(int argc, char *argv[])
{
    string infix;
    getline(cin, infix);
    string rpn;
    try { // convert the infix expression to RPN expression
        rpn = convertInfix(infix);
    } catch (int x) { // handle the exception
        cout << "ERROR: Parenthesis mismatch" << endl;
        return 0;
    }
    cout << rpn << endl;
    int result = 0;
    try {
        result = computeRPN(rpn);
        cout << result << endl;
    } catch (int x) {
        cout << "ERROR: Not enough operands" << endl;
    } catch (char a) {
        cout << "ERROR: Divide by zero" << endl;
    } catch (double y) {
        cout << "ERROR: Too many operands" << endl;
    }

    return 0;
}

string convertInfix(const string& infix) {
    Stack<char> opt;
    stringstream ss;
    ss << infix;
    string token;
    string rpn;
    while (ss >> token){
        if (isdigit(token[0])) { // when the first digit is digit, it should be an integer
            if (rpn.empty()) rpn += token;
            else rpn += " " + token;
        }
        else if (token != "(" && token != ")"){ // token is an operator
            while (!opt.empty()) {
                char* optTop = opt.pop();
                if (*optTop == '(') { // if the top element is (, nothing would happen, and break the loop
                    opt.push(optTop);
                    break;
                }
                else {
                    if ( (*optTop == '+' || *optTop == '-') && (token == "*" || token == "/") ) {
                        // top element has less precedence, nothing would happen
                        opt.push(optTop);
                        break;
                    }
                    else {
                        rpn += " ";
                        rpn += *optTop;
                        delete optTop;
                    }
                }
            }
            stringstream temp;
            temp << token;
            char optToPush;
            temp >> optToPush;
            opt.push(new char(optToPush));
        }
        else if (token == "(") {
            opt.push(new char('('));
        }
        else if (token == ")") {
            if (opt.empty()) throw 20; // mismatched parentheses
            char* optTop = opt.pop();
            while (*optTop != '(') {
                rpn += " ";
                rpn += *optTop;
                delete optTop;
                if (opt.empty()) throw 20;
                optTop = opt.pop();
            }
            if (*optTop == '(') delete optTop;
        }
    }
    // no more tokens to read
    while (!opt.empty()) {
        char* optTop = opt.pop();
        if (*optTop == '(' || *optTop == ')') throw 20; // mismatched parentheses
        rpn += " ";
        rpn += *optTop;
        delete optTop;
    }
    return rpn;
}

int computeRPN(string& rpn) {
    Stack<int> nums;
    stringstream ss;
    ss << rpn;
    string op;
    while (ss >> op) {
         if (isdigit(op[0])) { // an operand is found, push it to the stack
            stringstream temp;
            temp << op;
            int val;
            temp >> val;
            nums.push(new int(val));
         }
         else { // an operator is found
             if (nums.empty()) throw 3; // not enough operand
             int* operand2 = nums.pop();
             if (nums.empty()) { // not enough operand, handle the object being poped
                 delete operand2;
                 throw 3;
             }
             int* operand1 = nums.pop();
             switch (op[0]) {
                 case '+':
                     nums.push(new int(*operand1 + *operand2));
                     break;
                 case '-':
                     nums.push(new int(*operand1 - *operand2));
                     break;
                 case '*':
                     nums.push(new int (*operand1 * (*operand2)));
                     break;
                 case '/':
                     if (*operand2 == 0) { // divided by zero
                         delete operand1;
                         delete operand2;
                         throw 'a';
                     }
                     nums.push(new int(*operand1 / (*operand2)));
                     break;
                 default:
                     cout << "something wrong in calculation!" << endl;
                     break;
             }
             delete operand1;
             delete operand2;
         }
    }

    if (nums.size() != 1) {
        throw 2.0;
    }
    int *result = nums.pop();
    int valReturn = *result;
    delete result;
    return valReturn;
}