//
// Created by Ceren Duru Cinar on 24.10.2023.
//

#ifndef STACK_H
#define STACK_H


using namespace std;

template <class Type>
class Stack{
public:
    Stack();
    Stack(const Stack & rhs);
    ~Stack();
    bool isEmpty() const;
    void makeEmpty();
    void pop();
    void topAndPop(Type & popped);
    void push( Type & elm);
    const Type & top() const;

    const Stack & operator=( const Stack & rhs );

private:
    struct Node{
        Type element;
        Node * next;

        Node( const Type & e, Node * n= nullptr) : element(e), next( n )
        { }

    };

    Node * topOfStack;
};
#include "Stack.cpp"

#endif
