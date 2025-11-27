#pragma once
#include <string>
#include <iostream>

template<typename C>
class DeckFactory {

public: 
    // virtual function
    virtual void shuffle () = 0;
    virtual C* getNext() = 0;
    virtual bool isEmpty() const = 0;

    // destructor
    virtual ~DeckFactory() = default;



};

