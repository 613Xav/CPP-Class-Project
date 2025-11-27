#include "headerFiles/Player.h"
#include "headerFiles/Rubis.h"
#include <iostream>
#include <string>



Player::Player(const std::string& playerName, Side playeSide, bool isActive, int rubies) 
    : name(playerName), active(isActive), nRubies(rubies), 
    side(playeSide), displayEndOfGame(false) {}


std::ostream& operator<<(std::ostream&, const Player& player) {



    
};