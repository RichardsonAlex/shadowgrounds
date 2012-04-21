#ifndef container_Stack_h
#define container_Stack_h

//
// Stack class
// Copyright(C) Jukka Kokkonen, 2000-2001
//

#include <stack>
#include <cassert>
#include "StackEmptyException.h"


/* ---------------------------------- */
// Stack class (prototype) definition

template<typename T>
class Stack
{
  private:
    std::stack<T> mStack;

  public:
    Stack();
    ~Stack();
    bool isEmpty();
    void push(T data);
    //TODO don't throw by pointer
    T pop() throw (StackEmptyException *);
    T& peek() throw (StackEmptyException *);
};

template<typename T>
inline Stack<T>::Stack() {}

template<typename T>
inline Stack<T>::~Stack() {
    assert(mStack.empty());
}

template<typename T>
inline T& Stack<T>::peek()
{
    return mStack.top();
}

template<typename T>
inline bool Stack<T>::isEmpty()
{
    return mStack.empty();
}

template<typename T>
inline void Stack<T>::push(const T& data)
{
    mStack.push(data);
}

template<typename T>
inline T Stack<T>::pop() throw(StackEmptyException *)
{
    if (mStack.empty())
        throw new StackEmptyException();
    T ret = mStack.top;
    mStack.pop();
    return ret;
}
template<typename T>
inline T& Stack::peek() throw (StackEmptyException *)
{
    if (mStack.empty())
        throw new StackEmptyException();
    return mStack.top();
}

#endif
