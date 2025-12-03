#include "headerFiles/Board.h"
#include "headerFiles/Card.h"
#include <vector>
#include <iostream>
#include <stdexcept>

// Convertir les lettres et nombre en index
int Board::letterToIndex(const Letter& l) const {
    switch (l) {
    case Letter::A:
        return 0;
    case Letter::B:
        return 1;
    case Letter::C:
        return 2;
    case Letter::D:
        return 3;
    case Letter::E:
        return 4;
    default:
        throw OutOfRange();
    }
}

int Board::numberToIndex(const Number& n) const {
    switch (n) {
    case Number::_1:
        return 0;
    case Number::_2:
        return 1;
    case Number::_3:
        return 2;
    case Number::_4:
        return 3;
    case Number::_5:
        return 4;
    default:
        throw OutOfRange();
    }
}



bool Board::isValidPosition(const Letter& l, const Number& n) const {
    // Vérifier si la position est valide
    int letterPosition = letterToIndex(l);
    int numberPosition = numberToIndex(n);
    
    if (letterPosition > 4 || letterPosition < 0) {
        return false;
    }
    if (numberPosition > 4 || numberPosition < 0) {
        return false;
    }
    
    if (letterPosition == 2 && numberPosition == 2) {
        return false;
    }
    
    return true;
}


// construire le tableau
Board::Board() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = nullptr;
            faceUp[i][j] = false;
        }
    }
}

// verifier si carte est visible ou non
bool Board::isFaceUp(const Letter& letter, const Number& number) const {
    if (!isValidPosition(letter, number)) {
        throw OutOfRange();
    }
    int row = letterToIndex(letter);
    int col = numberToIndex(number);
    return faceUp[row][col];
}

// changer l'état de la carte
bool Board::turnFaceUp(const Letter& letter, const Number& number) {
    int letterPosition = letterToIndex(letter);
    int numberPosition = numberToIndex(number);

    if (!isValidPosition(letter, number)) {
        throw OutOfRange();
    }
    if (!faceUp[letterPosition][numberPosition]) {
        faceUp[letterPosition][numberPosition] = true;
        return true;  
    }
    return false;  
}

// change l'état de la carte
bool Board::turnFaceDown(const Letter& letter, const Number& number) {
    int letterPosition = letterToIndex(letter);
    int numberPosition = numberToIndex(number);

    if (!isValidPosition(letter, number)) {
        throw OutOfRange();
    }
    if (faceUp[letterPosition][numberPosition]) {
        faceUp[letterPosition][numberPosition] = false;
        return true;  
    }
    return false;  
}


// trouver une carte dans e tableay
Card* Board::getCard(const Letter& letter, const Number& number) {
    if (!isValidPosition(letter, number)) {
        throw OutOfRange();
    }
    int row = letterToIndex(letter);
    int col = numberToIndex(number);
    return grid[row][col];
}

void Board::setCard(const Letter& letter, const Number& number, Card* card) {
    if (!isValidPosition(letter, number)) {
        throw OutOfRange();
    }
    int row = letterToIndex(letter);
    int col = numberToIndex(number);
    grid[row][col] = card;
}

// Touner toute les cartes
void Board::allFacesDown() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            faceUp[i][j] = false;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {

    os << "Board Display : \n";
    // Afficher chaque ligne (A-E)
    for (int row = 0; row < Board::ROWS; ++row) {
        // Afficher les 3 sous-lignes pour chaque ligne de cartes
        for (int cardRow = 0; cardRow < 3; ++cardRow) {
            // Afficher la lettre de la ligne seulement sur la ligne du milieu
            if (cardRow == 1) {
                os << static_cast<char>('A' + row) << " ";
            } else {
                os << "  ";
            }
            
            // Afficher chaque colonne
            for (int col = 0; col < Board::COLS; ++col) {
                // Position centrale vide
                if (row == 2 && col == 2) {
                    os << "     ";
                } else {
                    Card* card = board.grid[row][col];
                    if (card && board.faceUp[row][col]) {
                        // Carte visible
                        os << (*card)(cardRow);
                    } else {
                        // Carte cachée
                        os << "_ZZZ_";
                    }
                }
                
                // Espace entre les cartes
                if (col != Board::COLS - 1) {
                    os << " ";
                }
            }
            os << std::endl;
        }
    }
    
    // Afficher les numéros de colonne en bas
    os << "  ";
    for (int col = 0; col < Board::COLS; ++col) {
        os << "  " << (col + 1) << "  ";
        if (col != Board::COLS - 1) {
            os << " ";
        }
    }
    os << std::endl;
    
    return os;
}

// destructeur
Board::~Board() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = nullptr;
        }
    }
}