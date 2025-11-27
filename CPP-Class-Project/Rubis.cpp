#include "headerFiles/Rubis.h"
#include "headerFiles/RubisDeck.h"
#include <stdexcept>

// Private constructor definition
Rubis::Rubis(int v) : valeur{v} {
    if (v < 1 || v > 4) {
        throw std::out_of_range("Rubis value must be between 1 and 4.");
    }
}

// Definition of conversion operator to int
Rubis::operator int() const {
    return valeur;
}

// Overloading the cout operator for rubis
std::ostream& operator<<(std::ostream& os, const Rubis& rubis) {
    os << static_cast<int>(rubis);
    return os;
}

/* Test later in case of issues
// Overloading the cout operator for Rubis
std::ostream& operator<<(std::ostream& os, const Rubis& rubis) {
    os << rubis.valeur;
    return os;
}*/

