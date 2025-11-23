#pragma once
#include <string>
#include <iostream>

class RubisDeck;

class Rubis {

    private:
        int valeur;

        Rubis(int v);
        
        friend class RubisDeck;


    public:

        operator int() const;
        friend std::ostream& operator<<(std::ostream& os, const Rubis& rubis);


};
