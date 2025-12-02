#include "headerFiles/RubisDeck.h"
#include <algorithm>
#include <random>

// Private constructor
// Build the physical rubis distribution:
// 3 cards with value 1
// 2 cards with value 2
// 1 card with value 3
// 1 card with value 4
RubisDeck::RubisDeck() : rubis{}, currentIndex{0} {
    // 3 x 1 rubis
    for (int i = 0; i < 3; ++i) {
        rubis.push_back(new Rubis(1));
    }

    // 2 x 2 rubis
    for (int i = 0; i < 2; ++i) {
        rubis.push_back(new Rubis(2));
    }

    // 1 x 3 rubis
    rubis.push_back(new Rubis(3));

    // 1 x 4 rubis
    rubis.push_back(new Rubis(4));

    // Start in a shuffled state
    shuffle();
}

// Singleton accessor
RubisDeck& RubisDeck::make_RubisDeck() {
    static RubisDeck instance; // created once, reused for entire program
    return instance;
}

// Shuffle implementation
void RubisDeck::shuffle() {
    if (rubis.empty()) {
        return;
    }

    /*// Seed the random generator -------------------------------------- Depricated, Verify Later
    std::srand(static_cast<unsigned>(std::time(nullptr)));*/

    // Create (once) a good random engine
    static std::mt19937 rng(std::random_device{}());

    // Shuffle the vector of Rubis* in place
    std::shuffle(rubis.begin(), rubis.end(), rng);

    // After shuffling, draw again from the beginning
    currentIndex = 0;
}

// Get next rubis
// Returns nullptr if there are no more rubies to draw.
Rubis* RubisDeck::getNext() {
    if (isEmpty()) {
        return nullptr;
    }
    return rubis[currentIndex++];
}

// Check if deck is empty
bool RubisDeck::isEmpty() const {
    return currentIndex >= rubis.size();
}

// Rubis deck destructor 
RubisDeck::~RubisDeck() {
    for (Rubis* r : rubis) {
        delete r;
    }
}
