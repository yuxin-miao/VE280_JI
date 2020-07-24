//
// Created by 86136 on 2020/7/22.
//

#ifndef PROJECT5_DLIST_IMPL_H
#define PROJECT5_DLIST_IMPL_H

#include <iostream>
#include "dlist.h"

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    node *front = new node;
    front->next = nullptr;
    front->prev = nullptr;
    front->op = op;
    if (isEmpty()) {
        first = last = front;
    } else {
        front->next = first;
        first->prev = front;
        first = front;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    node *back = new node;
    back->next = nullptr;
    back->prev = nullptr;
    back->op = op;
    if (isEmpty()) {
        first = last = back;
    } else {
        back->prev = last;
        last->next = back;
        last = back;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if(isEmpty()) throw emptyList{};
    node *victim = first;
    T* result = victim->op;
    if (first == last) first = last = nullptr;
    else {
        first = victim->next;
        first->prev = nullptr;
    }
    delete victim;
    return result;
}

template<class T>
T *Dlist<T>::removeBack() {
    if(isEmpty()) throw emptyList{};
    node *victim = last;
    T* result = victim->op;
    if (first == last) first = last = nullptr;
    else {
        last = victim->prev;
        last->next = nullptr;
    }
    delete victim;
    return result;
}

template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
    if(isEmpty()) return nullptr;
    node *victim = first;
    while (victim){
        if (cmp(victim->op, ref)) {
            T* result = victim->op;
            if (victim == first){
                removeFront();
            }
            else if (victim == last){
                removeBack();
            } else {
                node* temp1 = victim->prev;
                node* temp2 = victim->next;
                temp1->next = victim->next;
                temp2->prev = victim->prev;
                victim->prev = temp1;
                victim->next = temp2;
                delete victim;
            }
            return result;
        }
        victim = victim->next;
    }
    return nullptr;
}

template<class T>
Dlist<T>::Dlist() : first(0), last(0){
}

template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template<class T>
void Dlist<T>::removeAll() {
    while (!isEmpty()){
        T* front = removeFront();
        delete front;
    }
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if (this == &l) return;
    if (!isEmpty()) removeAll();
    node* temp = l.first;
    while(temp){
        T* copy = new T(*temp->op);
        insertBack(copy);
        temp = temp->next;
    }
}

template<class T>
Dlist<T>::Dlist(const Dlist &l) {
    first = nullptr;
    last = nullptr;
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if (this != &l) copyAll(l);
    return *this;
}

/*template<class T>
void Dlist<T>::print() const {
    node* itr = first;
    while (itr) {
        std::cout << *itr->op;
        itr = itr->next;
    }
    std::cout << std::endl;
}*/

#endif //PROJECT5_DLIST_IMPL_H
