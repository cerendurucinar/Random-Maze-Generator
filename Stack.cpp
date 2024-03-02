//
// Created by Ceren Duru Cinar on 24.10.2023.
//
#include "Stack.h"
using namespace std;

template <class Type>
Stack<Type>::Stack(){
    topOfStack = nullptr;
}

template <class Type>
Stack<Type>::Stack(const Stack<Type> & rhs) {
    this->makeEmpty();
    if (rhs.isEmpty()){
        topOfStack = nullptr;
    }
    else{
        Node* rhscurrent = rhs.topOfStack;
        Node * added = new Node(rhscurrent->element);
        Node * copyptr = added;
        this->topOfStack = added;
        rhscurrent = rhscurrent->next;
        while(rhscurrent != nullptr) {
            Node *add = new Node(rhscurrent->element);
            copyptr->next = add;
            copyptr = copyptr->next;
            rhscurrent = rhscurrent->next;
        }
    }
}

template <class Type>
Stack<Type>::~Stack(){
    makeEmpty();
}

template <class Type>
bool Stack<Type>::isEmpty() const {
    return (topOfStack == nullptr);
}

template <class Type>
void Stack<Type>::makeEmpty() {
    while (!isEmpty()){
        pop();
    }
}

template <class Type>
void Stack<Type>::push(Type & elm){
    Node * addedNode = new Node(elm, topOfStack);
    topOfStack = addedNode;
}

template <class Type>
const Type & Stack<Type>::top() const{
    return &topOfStack->element;
}

template <class Type>
void Stack<Type>::pop(){
    if (!isEmpty()){
        Node * current = topOfStack;
        topOfStack = topOfStack->next;
        delete current;
        current = nullptr;
    }
}

template <class Type>
void Stack<Type>::topAndPop(Type & popped){
    if (!isEmpty()){
        popped = topOfStack->element;
        pop();
    }

}

template <class Type>
const Stack<Type> & Stack<Type>::operator=(const Stack & rhs){
    if (this != &rhs){
        this->makeEmpty();
        if (rhs.isEmpty()){
            return *this;
        }
        Node* rhscurrent = rhs.topOfStack;
        Node * added = new Node(rhscurrent->element);
        Node * copyptr = added;
        this->topOfStack = added;
        rhscurrent = rhscurrent->next;
        while(rhscurrent != nullptr) {
            Node *add = new Node(rhscurrent->element);
            copyptr->next = add;
            copyptr = copyptr->next;
            rhscurrent = rhscurrent->next;
        }
    }
    return *this;
}