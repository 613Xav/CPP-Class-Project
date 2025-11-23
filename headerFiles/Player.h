#pragma once
#include <string>
#include <iostream>


// Required enum
enum class Side { top, bottom, left, right };

class Player {

    //class variables for player
    std::string name;  
    bool active;
    int nRubies;
    Side side;
    bool displayEndOfGame; 
    
public:
    // Player construction
    Player(const std::string& playerName = "", Side playerSide = Side::top, 
           bool isActive = true, int rubies = 0)
        : name(playerName), active(isActive), nRubies(rubies), side(playerSide), 
          displayEndOfGame(false) {}

    // Public functions for player
    std::string getName() const { return name; }
    void setActive(bool isActive); 
    bool isActive() const { return active; }
    int getNRubies() const { return nRubies; } 
    void addRubis(const Rubis& rubis);  // Need to include Rubis.h
    
    // Side methods
    Side getSide() const { return side; }
    void setSide(Side newSide) { side = newSide; }
    
    void setDisplayMode(bool endOfGame) { displayEndOfGame = endOfGame; }
    
    // Overloading cout for printing
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};