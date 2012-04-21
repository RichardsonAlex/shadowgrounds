#ifndef container_StackEmptyException_h
#define container_StackEmptyException_h

// #include "csp/CSPException.h"
#include <stdexcept>

class StackEmptyException : public std::range_error {
    virtual const char* what() const {
        return "Attempting to pop from empty stack!";
    }
}; //extends CSPException { };


#endif
