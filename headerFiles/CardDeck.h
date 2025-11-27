#pragma once
#include "DeckFactory.h"
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>

// Forward declaration (if needed)
class Card;

class CardDeck : public DeckFactory<Card> {
private:
    std::vector<Card*> cards;
    size_t currentIndex;
    
    // Private constructor 
    CardDeck();
    
    // Prevent copying and assignment
    CardDeck(const CardDeck&) = delete;
    CardDeck& operator=(const CardDeck&) = delete;

public:
    // Static singleton method - ONLY public way to get CardDeck
    static CardDeck& make_CardDeck();
    
    // Implement pure virtual functions from DeckFactory
    void shuffle() override;
    Card* getNext() override;
    bool isEmpty() const override;
    
    // Destructor
    ~CardDeck() override;
};