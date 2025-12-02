#include "headerFiles/Player.h"
#include "headerFiles/Rubis.h"
#include <iostream>
#include <string>

Player::Player(const std::string& playerName, Side playerSide, bool isActive, int rubies) 
    : name(playerName), active(isActive), nRubies(rubies), 
      side(playerSide), displayEndOfGame(false) {}

void Player::setActive(bool isActive) {
    active = isActive;
}

void Player::addRubis(const Rubis& rubis) {
    nRubies += static_cast<int>(rubis);
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    if(player.displayEndOfGame){
        os << player.name << ": " << player.nRubies << " rubis";
    } else {
        os << player.name << ": ";
        switch (player.side){
            case Side::top: 
                os << "top"; break;
            case Side::bottom: 
                os << "bottom"; break;
            case Side::left: 
                os << "left"; break;
            case Side::right: 
                os << "right"; break; 
        }
        os << " (" << (player.active ? "active" : "inactive") << ")";        
    }
    return os;
}