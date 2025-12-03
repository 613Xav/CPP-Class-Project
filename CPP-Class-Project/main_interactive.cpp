#include "headerFiles/Game.h"
#include "headerFiles/Player.h"
#include "headerFiles/Rules.h"
#include "headerFiles/CardDeck.h"
#include "headerFiles/RubisDeck.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// Fonction pour effacer l'ecran
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
        default: throw std::invalid_argument("Numero invalide");
    }
}

// Fonction pour obtenir une entree valide de l'utilisateur
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
        std::cout << "Entrez le numero (1-5) : ";
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Erreur : veuillez entrer un nombre\n";
        } else if (number >= 1 && number <= 5) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return number;
        } else {
            std::cout << "Erreur : le numero doit être entre 1 et 5\n";
        }
    }
}

// Fonction helper pour convertir Letter et Number a string
std::string positionToString(Letter l, Number n) {
    std::string letter;
    switch(l) {
        case Letter::A: letter = "A"; break;
        case Letter::B: letter = "B"; break;
        case Letter::C: letter = "C"; break;
        case Letter::D: letter = "D"; break;
        case Letter::E: letter = "E"; break;
    }
    std::string number = std::to_string(static_cast<int>(n) + 1);
    return letter + number;
}

// Fonction pour afficher l'etat du jeu en mode regular
void displayGameStateRegular(const Game& game, const Rules& rules) {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "       JEU MEMOARR! (MODE REGULAR)  \n";
    std::cout << "========================================\n\n";
    
    std::cout << game << std::endl;
    
    std::cout << "Manche : " << game.getRound() + 1 << " / 7\n";
    
    if (game.getCurrentCard()) {
        std::cout << "Derniere carte retournee :\n";
        // Afficher la derniere carte
    }
    std::cout << "========================================\n";
}

// Fonction pour afficher l'etat du jeu en mode expert (seulement les cartes devoilees)
void displayGameStateExpert(Game& game, const Rules& rules) {
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "        JEU MEMOARR! (MODE EXPERT)   \n";
    std::cout << "========================================\n\n";
    
    std::cout << "Manche : " << game.getRound() + 1 << " / 7\n\n";
    
    // Afficher seulement les cartes face visible
    std::cout << "Cartes devoilees :\n";
    std::cout << "-------------------\n";
    
    bool hasVisibleCards = false;
    Letter letters[] = {Letter::A, Letter::B, Letter::C, Letter::D, Letter::E};
    Number numbers[] = {Number::_1, Number::_2, Number::_3, Number::_4, Number::_5};
    
    std::vector<std::pair<Card*, std::string>> visibleCards;
    
    for (const auto& l : letters) {
        for (const auto& n : numbers) {
            // Skip center position C3
            if (l == Letter::C && n == Number::_3) continue;
            
            Card* card = game.getCard(l, n);
            // Display only face-up cards
            if (card && game.isFaceUp(l, n)) {
                hasVisibleCards = true;
                std::string pos = positionToString(l, n);
                visibleCards.push_back({card, pos});
            }
        }
    }
    
    if (!hasVisibleCards) {
        std::cout << "Aucune carte devoilee pour le moment.\n";
    } else {
        // Display all visible cards
        // Row 0 of all cards
        for (size_t i = 0; i < visibleCards.size(); ++i) {
            std::cout << (*(visibleCards[i].first))(0);
            if (i < visibleCards.size() - 1) std::cout << " ";
        }
        std::cout << "\n";
        
        // Row 1 of all cards
        for (size_t i = 0; i < visibleCards.size(); ++i) {
            std::cout << (*(visibleCards[i].first))(1);
            if (i < visibleCards.size() - 1) std::cout << " ";
        }
        std::cout << "\n";
        
        // Row 2 of all cards
        for (size_t i = 0; i < visibleCards.size(); ++i) {
            std::cout << (*(visibleCards[i].first))(2);
            if (i < visibleCards.size() - 1) std::cout << " ";
        }
        std::cout << "\n";
        
        // Position labels
        for (size_t i = 0; i < visibleCards.size(); ++i) {
            std::cout << visibleCards[i].second;
            if (i < visibleCards.size() - 1) std::cout << "    ";
        }
        std::cout << "\n";
    }
    
    std::cout << "========================================\n";
}

// Fonction pour afficher l'etat du jeu (wrapper qui appelle la bonne fonction selon le mode)
void displayGameState(Game& game, const Rules& rules, bool expertDisplayMode) {
    if (expertDisplayMode) {
        displayGameStateExpert(game, rules);
    } else {
        displayGameStateRegular(game, rules);
    }
}

// Fonction pour afficher les 3 cartes du milieu devant un joueur
void revealPlayerCards(Game& game, const Player& player) {
    Side playerSide = player.getSide();
    std::vector<std::pair<Letter, Number>> cardsToReveal;
    
    // Determiner les 3 cartes du milieu selon le cote du joueur
    if (playerSide == Side::top) {
        // Top: colonnes 2, 3, 4, rangée A (top row)
        cardsToReveal = {{Letter::A, Number::_2}, {Letter::A, Number::_3}, {Letter::A, Number::_4}};
    } else if (playerSide == Side::bottom) {
        // Bottom: colonnes 2, 3, 4, rangée E (bottom row)
        cardsToReveal = {{Letter::E, Number::_2}, {Letter::E, Number::_3}, {Letter::E, Number::_4}};
    } else if (playerSide == Side::left) {
        // Left: rangées B, C, D, colonne 1
        cardsToReveal = {{Letter::B, Number::_1}, {Letter::C, Number::_1}, {Letter::D, Number::_1}};
    } else if (playerSide == Side::right) {
        // Right: rangées B, C, D, colonne 5
        cardsToReveal = {{Letter::B, Number::_5}, {Letter::C, Number::_5}, {Letter::D, Number::_5}};
    }
    
    std::cout << "\n*** Les cartes de " << player.getName() << " (side " 
              << (playerSide == Side::top ? "TOP" : 
                  playerSide == Side::bottom ? "BOTTOM" :
                  playerSide == Side::left ? "LEFT" : "RIGHT") << ") ***\n";
    
    for (const auto& pos : cardsToReveal) {
        Card* card = game.getCard(pos.first, pos.second);
        if (card) {
            for (int row = 0; row < 3; ++row) {
                std::cout << (*card)(row) << std::endl;
            }
            std::cout << "---\n";
        }
    }
}

// Helper function to get animal type from card
FaceAnimal getCardAnimal(Card* card) {
    if (card) {
        return static_cast<FaceAnimal>(*card);
    }
    return FaceAnimal::Crab; // Default
}

// Helper function to handle Octopus effect
void handleOctopusEffect(Game& game, Letter l, Number n) {
    std::cout << "\n*** Effet Pieuvre: Echange avec une carte adjacente! ***\n";
    
    // Get possible adjacent positions
    std::vector<std::pair<Letter, Number>> adjacent;
    
    // Check all 4 neighbors
    if (l != Letter::A) adjacent.push_back({static_cast<Letter>(static_cast<int>(l) - 1), n}); // Up
    if (l != Letter::E) adjacent.push_back({static_cast<Letter>(static_cast<int>(l) + 1), n}); // Down
    if (n != Number::_1) adjacent.push_back({l, static_cast<Number>(static_cast<int>(n) - 1)}); // Left
    if (n != Number::_5) adjacent.push_back({l, static_cast<Number>(static_cast<int>(n) + 1)}); // Right
    
    if (adjacent.empty()) {
        std::cout << "Aucune carte adjacente disponible.\n";
        return;
    }
    
    std::cout << "Cartes adjacentes disponibles:\n";
    for (size_t i = 0; i < adjacent.size(); ++i) {
        std::cout << (i + 1) << " - " << positionToString(adjacent[i].first, adjacent[i].second) << "\n";
    }
    
    int choice;
    do {
        std::cout << "Choisissez une position (1-" << adjacent.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 || choice > static_cast<int>(adjacent.size()));
    
    Card* currentCard = game.getCard(l, n);
    Card* swapCard = game.getCard(adjacent[choice - 1].first, adjacent[choice - 1].second);
    
    // Swap cards
    game.setCard(l, n, swapCard);
    game.setCard(adjacent[choice - 1].first, adjacent[choice - 1].second, currentCard);
    
    std::cout << "Cartes echangees!\n";
}

// Helper function to handle Penguin effect
void handlePenguinEffect(Game& game, int roundNumber, int firstCardThisTurn) {
    if (roundNumber == 0 || firstCardThisTurn == 0) {
        std::cout << "\nEffet Pingouin: Impossible au premier tour ou sans autre carte visible.\n";
        return;
    }
    
    std::cout << "\n*** Effet Pingouin: Vous pouvez retourner une carte visible! ***\n";
    std::cout << "Entrez la position (ex: A1) ou appuyez Enter pour passer: ";
    
    std::string input;
    std::getline(std::cin, input);
    
    if (input.empty()) {
        std::cout << "Effet Pingouin ignore.\n";
        return;
    }
    
    if (input.length() >= 2) {
        char letter = input[0];
        int number = std::stoi(input.substr(1));
        
        try {
            Letter l = charToLetter(letter);
            Number n = intToNumber(number);
            
            if (game.isFaceUp(l, n)) {
                game.playCard(l, n); // This would reverse it again (face down)
                std::cout << "Carte retournee face cachee!\n";
            } else {
                std::cout << "Cette carte n'est pas visible.\n";
            }
        } catch (...) {
            std::cout << "Position invalide.\n";
        }
    }
}

// Helper function to handle Walrus effect
void handleWalrusEffect(Game& game, std::string& forbiddenPosition) {
    std::cout << "\n*** Effet Morse: Choisissez la position interdite au prochain joueur ***\n";
    std::cout << "Entrez la position (ex: A1): ";
    std::getline(std::cin, forbiddenPosition);
    std::cout << "Le prochain joueur ne peut pas choisir " << forbiddenPosition << "!\n";
}

// Helper function to handle Crab effect
void handleCrabEffect(bool& mustPlayAgain) {
    std::cout << "\n*** Effet Crabe: Vous devez jouer encore! ***\n";
    mustPlayAgain = true;
}

// Helper function to handle Turtle effect
void handleTurtleEffect(bool& skipNextPlayer) {
    std::cout << "\n*** Effet Tortue: Le prochain joueur saute son tour! ***\n";
    skipNextPlayer = true;
}

int main() {
    // Initialisation
    std::cout << "=== INITIALISATION DU JEU ===\n\n";
    
    // Creer le jeu et les regles
    Game game;
    Rules rules;
    
    // Demander le mode d'affichage
    int displayModeChoice;
    bool expertDisplayMode = false;
    do {
        std::cout << "Mode d'affichage :\n";
        std::cout << "1 - Mode Regular (affichage complet du plateau)\n";
        std::cout << "2 - Mode Expert (seulement les cartes devoilees)\n";
        std::cout << "Votre choix (1 ou 2) : ";
        std::cin >> displayModeChoice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayModeChoice = 0;
        }
    } while (displayModeChoice != 1 && displayModeChoice != 2);
    
    expertDisplayMode = (displayModeChoice == 2);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Demander le mode regles
    int rulesModeChoice;
    bool expertRulesMode = false;
    do {
        std::cout << "\nMode regles :\n";
        std::cout << "1 - Mode Regular (regles classiques)\n";
        std::cout << "2 - Mode Expert (animaux avec pouvoirs speciaux)\n";
        std::cout << "Votre choix (1 ou 2) : ";
        std::cin >> rulesModeChoice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            rulesModeChoice = 0;
        }
    } while (rulesModeChoice != 1 && rulesModeChoice != 2);
    
    expertRulesMode = (rulesModeChoice == 2);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Demander le nombre de joueurs
    int numPlayers;
    do {
        std::cout << "\nNombre de joueurs (2-4) : ";
        std::cin >> numPlayers;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            numPlayers = 0;
        }
    } while (numPlayers < 2 || numPlayers > 4);
    
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Noms des joueurs et assignation des cotes
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
    
    // Preparer le plateau
    populateBoard(game);
    
    std::cout << "\nAppuyez sur Enter pour commencer...";
    std::cin.get();
    
    // Boucle principale du jeu (7 manches)
    while (!rules.gameOver(game)) {
        // Debut d'une nouvelle manche
        displayGameState(game, rules, expertDisplayMode);
        std::cout << "\n=== MANCHE " << game.getRound() + 1 << " ===\n";
        
        // Reinitialiser pour la nouvelle manche
        game.resetRound();
        
        // Afficher 3 cartes en main devant chaque joueur actif
        for (int i = 0; i < numPlayers; ++i) {
            try {
                Player& p = game.getPlayer(sides[i]);
                if (p.isActive()) {
                    revealPlayerCards(game, p);
                }
            } catch (...) {}
        }
        
        std::cout << "\nAppuyez sur Enter pour continuer...";
        std::cin.get();
        
        // Boucle de la manche
        while (!rules.roundOver(game)) {
            // Pour chaque joueur (dans l'ordre des côtes)
            for (int i = 0; i < numPlayers; ++i) {
                try {
                    Player& currentPlayer = game.getPlayer(sides[i]);
                    
                    // Verifier si le joueur est actif
                    if (!currentPlayer.isActive()) {
                        continue;
                    }
                    
                    // Afficher l'etat du jeu
                    displayGameState(game, rules, expertDisplayMode);
                    
                    // Tour du joueur
                    std::cout << "\n>>> Tour de " << currentPlayer.getName() << " <<<\n";
                    std::cout << "Choisissez une carte a retourner :\n";
                    
                    // Obtenir la position
                    char letter = getLetterInput();
                    int number = getNumberInput();
                    
                    Letter l = charToLetter(letter);
                    Number n = intToNumber(number);
                    
                    // Verifier que la position n'est pas le centre
                    if (letter == 'C' && number == 3) {
                        std::cout << "Erreur : la position C3 est vide !\n";
                        std::cout << "Appuyez sur Enter pour reessayer...";
                        std::cin.get();
                        i--; // Refaire le tour
                        continue;
                    }
                    
                    // Retourner la carte
                    bool success = game.playCard(l, n);
                    if (!success) {
                        std::cout << "Carte deja visible ou position invalide !\n";
                        std::cout << "Appuyez sur Enter pour reessayer...";
                        std::cin.get();
                        i--; // Refaire le tour
                        continue;
                    }
                    
                    // Obtenir la carte retournee
                    Card* selectedCard = game.getCard(l, n);
                    if (selectedCard) {
                        std::cout << "\nVous avez retourne :\n";
                        for (int row = 0; row < 3; ++row) {
                            std::cout << (*selectedCard)(row) << std::endl;
                        }
                    }
                    
                    // Handle expert rules effects
                    bool mustPlayAgain = false;
                    bool skipNextPlayer = false;
                    std::string forbiddenPosition = "";
                    
                    if (expertRulesMode && selectedCard) {
                        FaceAnimal animal = getCardAnimal(selectedCard);
                        
                        switch(animal) {
                            case FaceAnimal::Octopus:
                                handleOctopusEffect(game, l, n);
                                break;
                            case FaceAnimal::Penguin:
                                handlePenguinEffect(game, game.getRound(), (game.getPreviousCard() != nullptr ? 1 : 0));
                                break;
                            case FaceAnimal::Walrus:
                                handleWalrusEffect(game, forbiddenPosition);
                                break;
                            case FaceAnimal::Crab:
                                handleCrabEffect(mustPlayAgain);
                                break;
                            case FaceAnimal::Turtle:
                                handleTurtleEffect(skipNextPlayer);
                                break;
                        }
                    }
                    
                    // Verifier si la carte est valide (sauf premiere carte)
                    if (game.getPreviousCard() && !rules.isValid(game)) {
                        std::cout << "\nCarte invalide ! " 
                                  << currentPlayer.getName() 
                                  << " est elimine de cette manche.\n";
                        currentPlayer.setActive(false);
                    } else {
                        std::cout << "\nCarte valide !\n";
                    }
                    
                    std::cout << "Appuyez sur Enter pour continuer...";
                    std::cin.get();
                    
                    // Verifier si la manche est terminee
                    if (rules.roundOver(game)) {
                        break;
                    }
                    
                } catch (const std::exception& e) {
                    std::cout << "Erreur : " << e.what() << std::endl;
                    std::cout << "Appuyez sur Enter pour continuer...";
                    std::cin.get();
                }
            }
        }
        
        // Fin de la manche, attribuer les rubis au gagnant
        std::cout << "\n=== FIN DE LA MANCHE " << game.getRound() + 1 << " ===\n";
        
        // Trouver le joueur gagnant
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
        
        // Passer a la manche suivante
        game.nextRound();
        
        if (!rules.gameOver(game)) {
            std::cout << "\nAppuyez sur Enter pour passer a la manche suivante...";
            std::cin.get();
        }
    }
    
    // Fin du jeu
    clearScreen();
    std::cout << "========================================\n";
    std::cout << "              FIN DU JEU !                \n";
    std::cout << "========================================\n\n";
    
    std::cout << "SCORES FINAUX :\n";
    std::cout << "===============\n";
    
    // Recuperer tous les joueurs avec leurs scores
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
    
    // Determiner le gagnant, celui avec le plus de rubis
    if (!allPlayers.empty()) {
        Player* grandWinner = allPlayers.back();
        std::cout << "\nFELICITATIONS !\n";
        std::cout << "Le grand gagnant est : " << grandWinner->getName() 
                  << " avec " << grandWinner->getNRubies() << " rubis !\n";
    }
    
    std::cout << "\nMerci d'avoir joue a Memoarr!\n";
    
    return 0;
}
