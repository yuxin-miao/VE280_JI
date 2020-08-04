//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template<class T>
List<T>::List(): first(0), last(0) {
}

template<class T>
bool List<T>::isEmpty() const {
    return !first;
}

template<class T>
void List<T>::insertBack(T val) {
    auto* new_last = new node_t<T>;
    new_last->next = nullptr;
    new_last->val = val;
    if (isEmpty()) {first = last = new_last;}
    else {
        last->next = new_last;
        last = new_last;
    }
}

template<class T>
T List<T>::removeFront() {
    if (isEmpty()) throw emptyList();
    T value = first->val;
    node_t<T>* victim = first;
    first = first->next;
    delete victim;
    return value;
}

template<class T>
const node_t<T> *List<T>::returnHead() const {
    return first;
}

template<class T>
void List<T>::copyFrom(const List &l) {
    if (!isEmpty()) removeAll();
    if (l.isEmpty()) return;
    node_t<T>* current = l.first;
    while(current) {
        insertBack(current->val);
        current = current->next;
    }
}

template<class T>
void List<T>::removeAll() {

    if (isEmpty()) return;
    node_t<T>* victim = first;
    first = first->next;
    delete victim;
    if (!isEmpty()) removeAll();
}

template<class T>
List<T>::List(const List &l) {
    first = last = nullptr;
    copyFrom(l);
}

template<class T>
List<T> &List<T>::operator=(const List &l) {
    if (this != &l) {
        removeAll();
        copyFrom(l);
    }
    return *this;
}

template<class T>
List<T>::~List() {
    removeAll();
}

void isLargerHelper(const node_t<int>* aPtr, const node_t<int>* bPtr, int& larger) {
    if (aPtr && bPtr) isLargerHelper(aPtr->next, bPtr->next, larger);
    if (!aPtr && bPtr) larger = 0; // a is shorter
    else if (!bPtr && aPtr) larger = 1; // b is shorter
    if (larger == -1 && aPtr && bPtr) { // same length
        if (aPtr->val > bPtr->val) larger = 1;
        else if (aPtr->val < bPtr->val) larger = 0;
    }
}

bool isLarger(const List<int> &a, const List<int> &b) {
    if (a.isEmpty() && b.isEmpty()) return false; // returns false if both a and b are empty
    const node_t<int>* aPtr = a.returnHead();
    const node_t<int>* bPtr = b.returnHead();
    int larger = -1;
    isLargerHelper(aPtr, bPtr, larger);
    return larger == 1;
}

List<int> Add(const List<int> &a, const List<int> &b) {
    if (a.isEmpty() && b.isEmpty()) return List<int>();
    List<int> sumResult;
    int carry = 0, sum;
    auto aPtr = a.returnHead();
    auto bPtr = b.returnHead();
    while (aPtr || bPtr) {
        sum = carry + (aPtr ? aPtr->val : 0) + (bPtr ? bPtr->val : 0); // if no digit, treat as zero
        carry = (sum >= 10) ? 1 : 0; // if sum larger than 10, update the carry
        sum %= 10; // if sum larger than 10, only keep the single digit
        sumResult.insertBack(sum);
        if (aPtr) aPtr = aPtr->next;
        if (bPtr) bPtr = bPtr->next;
    }
    if (carry == 1) {
        sumResult.insertBack(1);
    }
    return List<int>(sumResult);
}
#endif //INTLIST_IMPL_H

