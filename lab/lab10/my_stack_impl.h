/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_IMPL_H
#define MY_STACK_IMPL_H

#include <iostream>
#include "my_stack.h"


template <class T>
void Stack<T>::print()
{
    Node<T>* itr = head;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template<class T>
Stack<T>::Stack(): head(0){
}

template<class T>
Stack<T>::Stack(const Stack &s) {
    this->head = nullptr;
    copyFrom(s);
}

template<class T>
void Stack<T>::removeAll() {
    if (isEmpty()) return;
    while (head) {
        Node<T>* victim = head;
        head = head->next;
        delete victim;
    }
}

template<class T>
bool Stack<T>::isEmpty() const {
    return !head;
}
template<class T>
void Stack<T>::copyNode(Node<T> *node) {
    if (!node) return;
    copyNode(node->next);
    push(node->val);
}
template<class T>
void Stack<T>::copyFrom(const Stack &s) {
    if (!this->isEmpty()) removeAll();
    if (s.isEmpty()) return;
    copyNode(s.head);
}

template<class T>
void Stack<T>::push(T val) {
    auto* new_head = new Node<T>;
    new_head->next = head;
    new_head->val = val;
    head = new_head;
}

template<class T>
size_t Stack<T>::size() const {
    if (isEmpty()) return 0;
    size_t size_num = 0;
    Node<T>* temp = head;
    while (temp) {
        size_num++;
        temp = temp->next;
    }
    return size_num;
}

template<class T>
void Stack<T>::pop() {
    if (isEmpty()) throw stackEmpty();
    Node<T>* victim = head;
    T val = victim->val;
    head = head->next;
    delete victim;
    //return val;
}

template<class T>
T Stack<T>::top() const {
    if (isEmpty()) throw stackEmpty();
    return head->val;
}

template<class T>
Stack<T>::~Stack() {
    removeAll();
}

template<class T>
Stack<T> &Stack<T>::operator=(const Stack &s) {
    if (this != &s && !this->isEmpty()) {
        removeAll();
        copyFrom(s);
    }
    else if (this->isEmpty()) {
        copyFrom(s);
    }
    return *this;
}

template<class T>
void Stack<T>::reverseStack() {
    if (isEmpty()) return;

    Stack<T> s_temp = *this;
    Node<T>* new_head = s_temp.head;
    this->removeAll();
    while (new_head) {
        this->push(new_head->val);
        new_head = new_head->next;
    }
}



template <class T>
void reverse(Stack<T> &s) {
    s.reverseStack();
}
template <class T>
Stack<T> operator +(Stack<T> &s, T val) {
    Stack<T> new_s(s);
    new_s.reverseStack();
    new_s.push(val);
    new_s.reverseStack();
    return Stack<T>(new_s);

}

template <class T>
Stack<T> operator +(Stack<T> &first, Stack<T> &second) {
    Stack<T> result(first);
    result.reverseStack();
    Stack<T> temp(second);
    while (!temp.isEmpty()) {
        result.push(temp.top());
        temp.pop();
    }
    result.reverseStack();
    return Stack<T>(result);

}
#endif //MY_STACK_IMPL_H