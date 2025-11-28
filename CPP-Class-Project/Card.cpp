#include "headerFiles/Card.h"
#include "headerFiles/CardDeck.h"
#include <cctype>
#include <stdexcept>

Card::Card(FaceAnimal animal, FaceBackground background) 
    : animal(animal), background(background) {}

Card::operator FaceAnimal() const {
    return animal;
}

Card::operator FaceBackground() const {
    return background;
}

int Card::getNRows() const {
    return 3;
}

std::string Card::operator()(int row) const {
    if (row < 0 || row >= 3) {
        throw std::out_of_range("Row index must be between 0 and 2");
    }
    
    // Caractère de l'animal
    char animalChar;
    switch (animal) {
        case FaceAnimal::Crab:     animalChar = 'C'; break;
        case FaceAnimal::Penguin:  animalChar = 'P'; break;
        case FaceAnimal::Octopus:  animalChar = 'O'; break;
        case FaceAnimal::Turtle:   animalChar = 'T'; break;
        case FaceAnimal::Walrus:   animalChar = 'W'; break;
        default: throw std::invalid_argument("Unknown animal");
    }
    
    // Caractère de base de la couleur (en minuscule)
    char bgChar;
    switch (background) {
        case FaceBackground::Red:    bgChar = 'r'; break;
        case FaceBackground::Green:  bgChar = 'g'; break;
        case FaceBackground::Purple: bgChar = 'p'; break;
        case FaceBackground::Blue:   bgChar = 'b'; break;
        case FaceBackground::Yellow: bgChar = 'y'; break;
        default: throw std::invalid_argument("Unknown background");
    }
    
    // Construction des rangées
    switch (row) {
        case 0:
        case 2:
            return std::string("_") + 
                   std::string(1, std::toupper(bgChar)) + 
                   std::string(1, std::toupper(bgChar)) + 
                   std::string(1, std::toupper(bgChar)) + 
                   "_";
        case 1:
            return std::string("_") + 
                   std::string(1, bgChar) + 
                   std::string(1, animalChar) + 
                   std::string(1, bgChar) + 
                   "_";
        default:
            return "";
    }
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    for (int row = 0; row < card.getNRows(); ++row) {
        os << card(row) << std::endl;
    }
    return os;
}
