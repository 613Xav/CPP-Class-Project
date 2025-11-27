#pragma once
#include <string>
#include <iostream>

class RubisDeck;

class Rubis {

    private:
        //object variables for tubis
        int valeur;

        Rubis(int v);
        
        friend class RubisDeck;


    public:

        //overridng the cout operator
        operator int() const;
        friend std::ostream& operator<<(std::ostream& os, const Rubis& rubis);


};
