#pragma once
#include "DeckFactory.h"
#include "Rubis.h"
#include <vector>
#include <algorithm>
#include <random>

class RubisDeck : public DeckFactory<Rubis> {
private:
    std::vector<Rubis*> rubis;
    size_t currentIndex;
    
    // Constructeur privé - seulement accessible via make_RubisDeck()
    RubisDeck();
    
    // Empêcher la copie et l'assignation
    RubisDeck(const RubisDeck&) = delete;
    RubisDeck& operator=(const RubisDeck&) = delete;

public:
    // Méthode singleton statique - SEULE façon publique d'obtenir RubisDeck
    static RubisDeck& make_RubisDeck();
    
    // Implémentation des fonctions virtuelles pures de DeckFactory
    void shuffle() override;
    Rubis* getNext() override;
    bool isEmpty() const override;
    
    // Destructeur
    ~RubisDeck() override;
};