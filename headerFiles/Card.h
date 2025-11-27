#pragma once
#include <string>
#include <iostream>

// Forward declaration
class CardDeck;

// Énumérations pour les animaux et les couleurs
enum class FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
enum class FaceBackground { Red, Green, Purple, Blue, Yellow };

class Card {
private:
    FaceAnimal animal;
    FaceBackground background;
    
    // Constructeur privé - seulement CardDeck peut créer des cartes
    Card(FaceAnimal animal, FaceBackground background);
    
    // Déclaration d'amitié pour CardDeck
    friend class CardDeck;

public:
    // Opérateurs de conversion de type
    operator FaceAnimal() const;
    operator FaceBackground() const;
    
    // Méthode pour obtenir le nombre de rangées (toujours 3)
    int getNRows() const;
    
    // Opérateur () pour obtenir une rangée spécifique
    std::string operator()(int row) const;
    
    // Surcharge de l'opérateur << pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    
    // Empêcher la copie
    Card(const Card&) = delete;
    Card& operator=(const Card&) = delete;
    
    // Destructeur
    ~Card() = default;
};