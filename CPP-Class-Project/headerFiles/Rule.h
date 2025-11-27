#pragma once
#pragma once
#include "Game.h"
#include "Player.h"
#include <vector>
#include <memory>

class Rules {
public:

    //virtual methods allow other functions to overwrite then

    // Check if the current card selection is valid
    virtual bool isValid(const Game& game) const;
    
    // Check if the game is over (7 rounds reached)
    virtual bool gameOver(const Game& game) const;
    
    // Check if the current round is over (only one player left)
    virtual bool roundOver(const Game& game) const;
    
    // Get the next active player
    virtual const Player& getNextPlayer(const Game& game) const;
    
    // Virtual destructor 
    virtual ~Rules() = default;
    
    // copy constructor
    Rules(const Rules&) = delete;
    Rules& operator=(const Rules&) = delete;

protected:
    Rules() = default;
};