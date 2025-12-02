#include "headerFiles/Game.h"
#include "headerFiles/Player.h"
#include "headerFiles/Rules.h"
#include "headerFiles/CardDeck.h"
#include "headerFiles/RubisDeck.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// Fonction pour effacer l'écran (optionnel)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fonction pour remplir le plateau avec les cartes du deck
void populateBoard(Game& game) {
    CardDeck& deck = CardDeck::make_CardDeck();
    
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            // Sauter la position centrale (C3)
            if (row == 2 && col == 2) continue;
            
            Letter l = static_cast<Letter>(row);
            Number n = static_cast<Number>(col);
            
            Card* card = deck.getNext();
            if (card) {
                game.setCard(l, n, card);
            }
        }
    }
}

// Fonctions de conversion
Letter charToLetter(char c) {
    switch (toupper(c)) {
        case 'A': return Letter::A;
        case 'B': return Letter::B;
        case 'C': return Letter::C;
        case 'D': return Letter::D;
        case 'E': return Letter::E;
        default: throw std::invalid_argument("Lettre invalide");
    }
}

Number intToNumber(int n) {
    switch (n) {
        case 1: return Number::_1;
        case 2: return Number::_2;
        case 3: return Number::_3;
        case 4: return Number::_4;
        case 5: return Number::_5;
        default: throw std::invalid_argument("Numéro invalide");
    }
}

// Fonction pour obtenir une entrée valide de l'utilisateur
char getLetterInput() {
    char letter;
    while (true) {
        std::cout << "Entrez la lettre (A-E) : ";
        std::cin >> letter;
        letter = toupper(letter);
        if (letter >= 'A' && letter <= 'E') {
            return letter;
        }
        std::cout << "Erreur : la lettre doit être entre A et E\n";
    }
}

int getNumberInput() {
    int number;
    while (true) {
        std::cout << "Entrez le numéro (1-5) : ";
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur : veuillez entrer un nombre\n";
        } else if (number >= 1 && number <= 5) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return number;
        } else {
            std::cout << "Erreur : le numéro doit être entre 1 et 5\n";
        }
    }
}

// Fonction pour afficher l'état du jeu
void displayGameState(const Game& game, const Rules& rules) {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "           JEU MEMOARR!                \n";
    std::cout << "========================================\n\n";
    
    std::cout << game << std::endl;
    
    std::cout << "Manche : " << game.getRound() + 1 << " / 7\n";
    
    if (game.getCurrentCard()) {
        std::cout << "Dernière carte retournée :\n";
        // Afficher la dernière carte
    }
    std::cout << "========================================\n";
}

int main() {
    // Initialisation
    std::cout << "=== INITIALISATION DU JEU ===\n\n";
    
    // Créer le jeu et les règles
    Game game;
    Rules rules;
    
    // Demander le nombre de joueurs
    int numPlayers;
    do {
        std::cout << "Nombre de joueurs (2-4) : ";
        std::cin >> numPlayers;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            numPlayers = 0;
        }
    } while (numPlayers < 2 || numPlayers > 4);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Noms des joueurs et assignation des côtés
    std::vector<std::string> playerNames;
    std::vector<Side> sides = {Side::top, Side::bottom, Side::left, Side::right};
    
    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Nom du joueur " << (i + 1) << " : ";
        std::getline(std::cin, name);
        playerNames.push_back(name);
        
        // Ajouter le joueur au jeu
        game.addPlayer(Player(name, sides[i]));
    }
    
    // Préparer le plateau
    populateBoard(game);
    
    std::cout << "\nAppuyez sur Entrée pour commencer...";
    std::cin.get();
    
    // Boucle principale du jeu (7 manches)
    while (!rules.gameOver(game)) {
        // Début d'une nouvelle manche
        displayGameState(game, rules);
        std::cout << "\n=== MANCHE " << game.getRound() + 1 << " ===\n";
        
        // Réinitialiser pour la nouvelle manche
        game.resetRound();
        
        // Afficher 3 cartes devant chaque joueur (simplifié)
        std::cout << "Les joueurs regardent 3 cartes devant eux...\n";
        std::cout << "Appuyez sur Entrée pour continuer...";
        std::cin.get();
        
        // Boucle de la manche
        while (!rules.roundOver(game)) {
            // Pour chaque joueur (dans l'ordre des côtés)
            for (int i = 0; i < numPlayers; ++i) {
                try {
                    Player& currentPlayer = game.getPlayer(sides[i]);
                    
                    // Vérifier si le joueur est actif
                    if (!currentPlayer.isActive()) {
                        continue;
                    }
                    
                    // Afficher l'état du jeu
                    displayGameState(game, rules);
                    
                    // Tour du joueur
                    std::cout << "\n>>> Tour de " << currentPlayer.getName() << " <<<\n";
                    std::cout << "Choisissez une carte à retourner :\n";
                    
                    // Obtenir la position
                    char letter = getLetterInput();
                    int number = getNumberInput();
                    
                    Letter l = charToLetter(letter);
                    Number n = intToNumber(number);
                    
                    // Vérifier que la position n'est pas le centre
                    if (letter == 'C' && number == 3) {
                        std::cout << "Erreur : la position C3 est vide !\n";
                        std::cout << "Appuyez sur Entrée pour réessayer...";
                        std::cin.get();
                        i--; // Refaire le tour
                        continue;
                    }
                    
                    // Retourner la carte
                    bool success = game.playCard(l, n);
                    if (!success) {
                        std::cout << "Carte déjà visible ou position invalide !\n";
                        std::cout << "Appuyez sur Entrée pour réessayer...";
                        std::cin.get();
                        i--; // Refaire le tour
                        continue;
                    }
                    
                    // Obtenir la carte retournée
                    Card* selectedCard = game.getCard(l, n);
                    if (selectedCard) {
                        std::cout << "\nVous avez retourné :\n";
                        for (int row = 0; row < 3; ++row) {
                            std::cout << (*selectedCard)(row) << std::endl;
                        }
                    }
                    
                    // Vérifier si la carte est valide (sauf première carte)
                    if (game.getPreviousCard() && !rules.isValid(game)) {
                        std::cout << "\n❌ Carte invalide ! " 
                                  << currentPlayer.getName() 
                                  << " est éliminé de cette manche.\n";
                        currentPlayer.setActive(false);
                    } else {
                        std::cout << "\n✅ Carte valide !\n";
                    }
                    
                    std::cout << "Appuyez sur Entrée pour continuer...";
                    std::cin.get();
                    
                    // Vérifier si la manche est terminée
                    if (rules.roundOver(game)) {
                        break;
                    }
                    
                } catch (const std::exception& e) {
                    std::cout << "Erreur : " << e.what() << std::endl;
                    std::cout << "Appuyez sur Entrée pour continuer...";
                    std::cin.get();
                }
            }
        }
        
        // Fin de la manche - attribuer les rubis au gagnant
        std::cout << "\n=== FIN DE LA MANCHE " << game.getRound() + 1 << " ===\n";
        
        // Trouver le joueur actif (gagnant)
        Player* winner = nullptr;
        for (int i = 0; i < numPlayers; ++i) {
            try {
                Player& p = game.getPlayer(sides[i]);
                if (p.isActive()) {
                    winner = &p;
                    break;
                }
            } catch (...) {}
        }
        
        if (winner) {
            RubisDeck& rubisDeck = RubisDeck::make_RubisDeck();
            Rubis* rubis = rubisDeck.getNext();
            if (rubis) {
                winner->addRubis(*rubis);
                std::cout << winner->getName() << " gagne " 
                          << static_cast<int>(*rubis) << " rubis !\n";
            } else {
                std::cout << "Plus de rubis disponibles !\n";
            }
        } else {
            std::cout << "Aucun gagnant cette manche.\n";
        }
        
        // Passer à la manche suivante
        game.nextRound();
        
        if (!rules.gameOver(game)) {
            std::cout << "\nAppuyez sur Entrée pour passer à la manche suivante...";
            std::cin.get();
        }
    }
    
    // Fin du jeu
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "           FIN DU JEU !                \n";
    std::cout << "========================================\n\n";
    
    std::cout << "SCORES FINAUX :\n";
    std::cout << "===============\n";
    
    // Récupérer tous les joueurs avec leurs scores
    std::vector<Player*> allPlayers;
    for (int i = 0; i < numPlayers; ++i) {
        try {
            Player& p = game.getPlayer(sides[i]);
            allPlayers.push_back(&p);
        } catch (...) {}
    }
    
    // Trier les joueurs par nombre de rubis (du moins au plus)
    std::sort(allPlayers.begin(), allPlayers.end(), 
              [](const Player* a, const Player* b) {
                  return a->getNRubies() < b->getNRubies();
              });
    
    // Afficher les scores
    for (const auto& player : allPlayers) {
        player->setDisplayMode(true);
        std::cout << *player << std::endl;
    }
    
    // Déterminer le gagnant (celui avec le plus de rubis)
    if (!allPlayers.empty()) {
        Player* grandWinner = allPlayers.back();
        std::cout << "\n🎉 FÉLICITATIONS ! 🎉\n";
        std::cout << "Le grand gagnant est : " << grandWinner->getName() 
                  << " avec " << grandWinner->getNRubies() << " rubis !\n";
    }
    
    std::cout << "\nMerci d'avoir joué à Memoarr!\n";
    
    return 0;
}
