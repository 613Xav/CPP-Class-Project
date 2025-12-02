#include "headerFiles/Game.h"
#include "headerFiles/Player.h"
#include "headerFiles/CardDeck.h"
#include "headerFiles/RubisDeck.h"
#include "headerFiles/Rules.h"
#include <iostream>
#include <vector>

void populateBoard(Game& game) {
    CardDeck& deck = CardDeck::make_CardDeck();
    
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (row == 2 && col == 2) continue; // Centre vide
            
            Letter l = static_cast<Letter>(row);
            Number n = static_cast<Number>(col);
            
            Card* card = deck.getNext();
            if (card) {
                game.setCard(l, n, card);
            }
        }
    }
}

int main() {
    std::cout << "=== JEU MEMOARR! ===\n\n";
    
    // Initialisation
    Game game;
    Rules rules;
    
    // Ajouter joueurs
    std::cout << "Ajout des joueurs...\n";
    game.addPlayer(Player("Alice", Side::left));
    game.addPlayer(Player("Bob", Side::right));
    game.addPlayer(Player("Charlie", Side::top));
    game.addPlayer(Player("Diana", Side::bottom));
    
    // Remplir le plateau
    std::cout << "Preparation du plateau...\n";
    populateBoard(game);
    
    std::cout << "\n=== DEBUT DE LA PARTIE ===\n";
    
    // Boucle de jeu simplifiée
    int round = 0;
    while (!rules.gameOver(game)) {
        std::cout << "\n--- Manche " << (round + 1) << " ---\n";
        std::cout << game << std::endl;
        
        // Logique simplifiée du tour
        std::cout << "Tour en cours...\n";
        
        round++;
        // Pour un vrai jeu, ajouter la logique des tours ici
        
        if (round >= 7) break;
    }
    
    std::cout << "\n=== FIN DU JEU ===\n";
    std::cout << "Resultats finaux:\n";
    
    // Afficher les scores finaux
    std::cout << game << std::endl;
    
    return 0;
}