#pragma once
#include <string>
#include <iostream>

class RubisDeck;

class Rubis {

    private:
        // Object variables for Rubis
        int valeur; // Value of the rubis
        Rubis(int v); // Private constructor
        friend class RubisDeck; // Friend class declaration

    public:
        // Overloading stream insertion & converion operator
        operator int() const; // Declaration of conversion operator
        friend std::ostream& operator<<(std::ostream& os, const Rubis& rubis);
};
