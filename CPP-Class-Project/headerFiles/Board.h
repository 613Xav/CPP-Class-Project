#pragma once
#include "Card.h"
#include <vector>
#include <iostream>
#include <stdexcept>

// Énumérations pour les positions
enum class Letter { A, B, C, D, E };
enum class Number { _1, _2, _3, _4, _5 };

// Exceptions personnalisées
class OutOfRange : public std::exception {
public:
    const char* what() const noexcept override {
        return "Position invalide: lettre ou numero hors limites";
    }
};

class NoMoreCards : public std::exception {
public:
    const char* what() const noexcept override {
        return "Plus de cartes disponibles pour construire le plateau";
    }
};

class Board {
private:
    static const int ROWS = 5;
    static const int COLS = 5;
    Card* grid[ROWS][COLS];
    bool faceUp[ROWS][COLS];
    
    int letterToIndex(const Letter& l) const;
    int numberToIndex(const Number& n) const;
    bool isValidPosition(const Letter& l, const Number& n) const;

public:
    // Constructeur 
    Board();
    
    // Destructeur
    ~Board();
    
    // Méthodes de classe
    bool isFaceUp(const Letter&, const Number&) const;
    bool turnFaceUp(const Letter&, const Number&);
    bool turnFaceDown(const Letter&, const Number&);
    Card* getCard(const Letter&, const Number&);
    void setCard(const Letter&, const Number&, Card*);
    void allFacesDown();
    
    // Surcharge de l'opérateur cout
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    
    // Empêcher la copie
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};