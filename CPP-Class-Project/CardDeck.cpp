#include "headerFiles/DeckFactory.h"
#include "headerFiles/CardDeck.h"
#include "headerFiles/Card.h"
#include <algorithm>
#include <random>
#include <chrono>



CardDeck::CardDeck() : currentIndex(0) {
    // Créer les 25 combinaisons de cartes (5 animaux × 5 couleurs)
    for (int animal = 0; animal < 5; ++animal) {
        for (int color = 0; color < 5; ++color) {
            // Convertir les indices en énumérations
            FaceAnimal animalEnum = static_cast<FaceAnimal>(animal);
            FaceBackground colorEnum = static_cast<FaceBackground>(color);
            
            // Créer une nouvelle carte (accessible grâce à friend)
            cards.push_back(new Card(animalEnum, colorEnum));
        }
    }
    
    // Mélanger initialement le deck
    shuffle();
}



CardDeck& CardDeck::make_CardDeck() {
    static CardDeck instance;
    return instance;
}


void CardDeck::shuffle() {
    // Générer une seed aléatoire
    std::random_device rd;
    std::mt19937 g(rd());
    
    // Mélanger
    std::shuffle(cards.begin(), cards.end(), g);
    currentIndex = 0;
}


Card* CardDeck::getNext() {
    if (isEmpty()) {
        return nullptr;
    }
    return cards[currentIndex++];
}



bool CardDeck::isEmpty() const {
    return currentIndex >= cards.size();
}


CardDeck::~CardDeck() {
    // Libérer la mémoire de toutes les cartes
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
    currentIndex = 0;
}