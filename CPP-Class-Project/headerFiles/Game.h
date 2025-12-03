#pragma once
#include "Board.h"
#include "Player.h"
#include "Card.h"
#include <vector>
#include <memory>
#include <iostream>

class Game {
private:
    Board board;
    std::vector<std::unique_ptr<Player>> players;
    const Card* previousCard;
    const Card* currentCard;
    int currentRound;
    
    // Trouver un joueur par son côté
    Player* findPlayerBySide(Side side);

public:
    // Constructeur
    Game();
    
    // méthodes de classes
    int getRound() const;
    void addPlayer(const Player& player);
    Player& getPlayer(Side side);
    const Player& getPlayer(Side side) const;
    const Card* getPreviousCard() const;
    const Card* getCurrentCard() const;
    void setCurrentCard(const Card* card);
    Card* getCard(const Letter& l, const Number& n);
    void setCard(const Letter& l, const Number& n, Card* card);
    
    // méthodes supplémentaires utiles
    void nextRound();
    void resetRound();
    size_t getNumPlayers() const;
    bool playCard(const Letter& l, const Number& n);  // Optionnel
    bool isFaceUp(const Letter& l, const Number& n) const;  // Check if card is face up
    
    // pour compter les joueurs actifs
    int countActivePlayers() const;
    
    
    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    
    // Empêcher la copie
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};
