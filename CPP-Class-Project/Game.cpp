#include "headerFiles/Game.h"
#include <stdexcept>

Game::Game() : previousCard(nullptr), currentCard(nullptr), currentRound(0) {}

int Game::getRound() const {
    return currentRound;
}

// ajoute un joueur

void Game::addPlayer(const Player& player) {
    players.push_back(std::make_unique<Player>(player));
}

// retourne un pointeur vers le joueur choisi
Player& Game::getPlayer(Side side) {
    for (auto& player : players) {
        if (player->getSide() == side) {
            return *player;
        }
    }
    throw std::runtime_error("Player not found");
}

const Card* Game::getPreviousCard() const {
    return previousCard;
}

const Card* Game::getCurrentCard() const {
    return currentCard;
}

void Game::setCurrentCard(const Card* card) {
    previousCard = currentCard;
    currentCard = card;
}

Card* Game::getCard(const Letter& l, const Number& n) {
    return board.getCard(l, n);
}

// set la carte
void Game::setCard(const Letter& l, const Number& n, Card* card) {
    board.setCard(l, n, card);
}

//imprime l'éraut du jeu
std::ostream& operator<<(std::ostream& os, const Game& game) {
    // Afficher le board
    os << game.board;
    
    // Afficher les joueurs
    os << "\nPlayers:\n";
    for (const auto& player : game.players) {
        // Déterminer si c'est la fin du jeu
        bool endOfGame = (game.currentRound >= 7);
        player->setDisplayMode(endOfGame);
        os << *player << "\n";
    }
    
    os << "Round: " << game.currentRound << "/7\n";
    
    return os;
}