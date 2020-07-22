#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include <iostream>
#include "dlist.h"

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
Dlist<T>::Dlist():first(0), last(0) {
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    node* temp = new node;
    temp->op = op;
    temp->next = nullptr;
    temp->prev = nullptr;
    if (isEmpty()) first = last = temp;
    else {
        temp->next = first;
        temp->prev = nullptr;
        first->prev = temp;
        first = temp;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    node* temp = new node;
    temp->op = op;
    temp->prev = nullptr;
    temp->next = nullptr;
    if (isEmpty()) first = last = temp;
    else {
        temp->prev = last;
        temp->next = nullptr;
        last->next = temp;
        last = temp;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()) throw emptyList();
    node* victim = first;
    T* val = victim->op;
    if (first == last) first = last = nullptr;
    else {
        first = first->next;
        first->prev = nullptr;
    }
    delete victim;
    return val;
}

template<class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()) throw emptyList();
    node* victim = last;
    T* val = victim->op;
    if (first == last) first = last = nullptr;
    else {
        last = last->prev;
        last->next = nullptr;
    }
    delete victim;
    return val;
}

template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
    node* itr = first;
    while (itr) {
        if (cmp(itr->op, ref)) {
            T* val = nullptr;
            if (itr->prev && itr->next) {
                node* temp_prev = itr->prev;
                temp_prev->next = itr->next;
                itr->prev = temp_prev;
                node *temp_next = itr->next;
                temp_next->prev = itr->prev;
                itr->next = temp_next;
                val = itr->op;
                delete itr;
            }
            else if (!itr->prev) { // itr is the first element or the only element
                val = removeFront();
            }
            else if (!itr->next) { // itr is the last element
                val = removeBack();
            }
            return val;
        }
        itr = itr->next;
    }
    return nullptr;
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if (this == &l) return;
    if (!this->isEmpty()) removeAll();
    if (l.isEmpty()) return;
    node* itr = l.first;
    while (itr) {
        T* copy = new T(*itr->op);
        this->insertBack(copy);
        itr = itr->next;
    }
}

template<class T>
void Dlist<T>::removeAll() {
    if(isEmpty()) return;
    node* itr = first;
    while (itr) {
        T* op = removeFront();
        delete op;
        itr = first;
    }
}

template<class T>
Dlist<T>::Dlist(const Dlist &l) {
    this->first = nullptr;
    this->last = nullptr;
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if (this != &l && !isEmpty()) {
        removeAll();
        copyAll(l);
    }
    else if (this->isEmpty()) copyAll(l);
    return *this;
}

template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}
/*
template<class T>
void Dlist<T>::print() const {
    node* itr = first;
    while (itr) {
        std::cout << *itr->op;
        itr = itr->next;
    }
    std::cout << std::endl;
}
*/

#endif //DLIST_IMPL_H
