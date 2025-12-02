#include "headerFiles/Rules.h"
#include "headerFiles/Card.h"
#include "headerFiles/Game.h"


bool Rules::isValid(const Game& game) const {
    const Card* prev = game.getPreviousCard();
    const Card* curr = game.getCurrentCard();
    
    // Première carte toujours valide
    if (!prev) return true;
    if (!curr) return false;
    
    // Même animal ou même couleur
    FaceAnimal pa = *prev;
    FaceAnimal ca = *curr;
    FaceBackground pb = *prev;
    FaceBackground cb = *curr;
    
    return (pa == ca) || (pb == cb);
}

bool Rules::gameOver(const Game& game) const {
    return game.getRound() >= 7;
}

bool Rules::roundOver(const Game& game) const {
    // La manche se termine quand il reste 1 joueur actif ou moins
    return game.countActivePlayers() <= 1;
}

const Player& Rules::getNextPlayer(const Game& game) const {
    // Parcourt tous les joueurs et retourne le premier actif
    // Implémentation simple: on suppose que les côtés sont dans l'ordre
    Side sides[] = {Side::top, Side::bottom, Side::left, Side::right};
    
    for (Side side : sides) {
        try {
            const Player& player = game.getPlayer(side);
            if (player.isActive()) {
                return player;
            }
        } catch (...) {
            // Ce côté n'a pas de joueur, on continue
        }
    }
    
    throw std::runtime_error("No active players found");
}
