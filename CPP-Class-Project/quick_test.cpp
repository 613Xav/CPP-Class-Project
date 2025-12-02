#include "headerFiles/Game.h"
#include "headerFiles/Player.h"
#include "headerFiles/CardDeck.h"
#include "headerFiles/RubisDeck.h"
#include <iostream>

int main() {
    std::cout << "Quick System Test: \n";
 
    
    // 1. Test singleton decks
    std::cout << "1. Testing CardDeck... ";
    CardDeck& cd = CardDeck::make_CardDeck();
    cd.shuffle();
    std::cout << "OK (shuffled)\n";
    
    // 2. Test RubisDeck
    std::cout << "2. Testing RubisDeck... ";
    RubisDeck& rd = RubisDeck::make_RubisDeck();
    rd.shuffle();
    std::cout << "OK (shuffled)\n";
    
    // 3. Test Game with Players
    std::cout << "3. Testing Game with Players... ";
    Game game;
    game.addPlayer(Player("Test1", Side::left));
    game.addPlayer(Player("Test2", Side::right));
    std::cout << "OK\n";
    
    // 4. Display test
    std::cout << "4. Testing display...\n";
    std::cout << game << std::endl;
        return 0;
}