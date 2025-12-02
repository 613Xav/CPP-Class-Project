#include "headerFiles/Game.h"
#include <stdexcept>
#include <iostream>

// Constructeur
Game::Game() : previousCard(nullptr), currentCard(nullptr), currentRound(0) {}

// Retourne le numéro de la manche actuelle
int Game::getRound() const {
    return currentRound;
}

// Ajoute un joueur
void Game::addPlayer(const Player& player) {
    players.push_back(std::make_unique<Player>(player));
}

// Retourne un pointeur vers le joueur choisi (version non-const)
Player& Game::getPlayer(Side side) {
    for (auto& player : players) {
        if (player->getSide() == side) {
            return *player;
        }
    }
    throw std::runtime_error("Player not found");
}

// Version const de getPlayer
const Player& Game::getPlayer(Side side) const {
    for (const auto& player : players) {
        if (player->getSide() == side) {
            return *player;
        }
    }
    throw std::runtime_error("Player not found for this side");
}

// Retourne la carte précédente
const Card* Game::getPreviousCard() const {
    return previousCard;
}

// Retourne la carte actuelle
const Card* Game::getCurrentCard() const {
    return currentCard;
}

// Définit la carte actuelle
void Game::setCurrentCard(const Card* card) {
    previousCard = currentCard;
    currentCard = card;
}

// Retourne une carte à une position donnée
Card* Game::getCard(const Letter& l, const Number& n) {
    return board.getCard(l, n);
}

// Place une carte à une position donnée
void Game::setCard(const Letter& l, const Number& n, Card* card) {
    board.setCard(l, n, card);
}

// Réinitialise la manche
void Game::resetRound() {
    // Retourner toutes les cartes face cachée
    board.allFacesDown();
    
    // Réactiver tous les joueurs
    for (auto& player : players) {
        player->setActive(true);
    }
    
    // Réinitialiser les cartes
    previousCard = nullptr;
    currentCard = nullptr;
}

// Passe à la manche suivante
void Game::nextRound() {
    currentRound++;
}

// Retourne le nombre de joueurs
size_t Game::getNumPlayers() const {
    return players.size();
}

// Trouve un joueur par son côté (privée)
Player* Game::findPlayerBySide(Side side) {
    for (auto& player : players) {
        if (player->getSide() == side) {
            return player.get();
        }
    }
    return nullptr;
}

// Joue une carte (retourne la carte face visible)
bool Game::playCard(const Letter& l, const Number& n) {
    try {
        // Obtenir la carte
        Card* card = board.getCard(l, n);
        if (!card) {
            return false;
        }
        
        // Retourner la carte face visible
        if (!board.turnFaceUp(l, n)) {
            return false;  // Déjà face visible
        }
        
        // Mettre à jour les cartes courantes
        previousCard = currentCard;
        currentCard = card;
        
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erreur dans playCard: " << e.what() << std::endl;
        return false;
    }
}

// Compte le nombre de joueurs actifs
int Game::countActivePlayers() const {
    int count = 0;
    for (const auto& player : players) {
        if (player->isActive()) {
            count++;
        }
    }
    return count;
}

// Opérateur d'affichage pour le jeu
std::ostream& operator<<(std::ostream& os, const Game& game) {
    // Afficher le plateau
    os << game.board;
    
    // Afficher les joueurs
    os << "\nJoueurs :\n";
    os << "---------\n";
    
    for (const auto& player : game.players) {
        // Déterminer si c'est la fin du jeu
        bool endOfGame = (game.currentRound >= 7);
        player->setDisplayMode(endOfGame);
        os << *player << "\n";
    }
    
    os << "\nManche : " << (game.currentRound + 1) << " / 7\n";
    
    // Afficher la dernière carte si elle existe
    if (game.currentCard) {
        os << "\nDernière carte retournée :\n";
        os << *(game.currentCard);
    }
    
    return os;
}
