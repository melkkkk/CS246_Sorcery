module board;

import plard;
import state;
import ascii_graphics;

import minion;
import ritual;
import enchantment;
import spell;
import state;

import <vector>;
import <string>;
import <iostream>;
import <memory>;

// PRINTING FUNCTIONS

// helper function that takes a Card and creates a corresponding card_template_t based on the type of card
card_template_t convertCard(std::unique_ptr<Card>& card){
    if (auto temp = dynamic_cast<Minion*>(card.get())) {
        // checking what type of minion it is
        if (temp->getHasAbilityO() && (temp->getAbilityCost() < 0)){
            return display_minion_triggered_ability(temp->getName(), 
                    temp->getCost(), temp->getAttack(), temp->getDefense(), temp->getDesc());
        } else if (temp->getHasAbilityO()) {
            return display_minion_activated_ability(temp->getName(), temp->getCost(), 
                    temp->getAttack(), temp->getDefense(), temp->getAbilityCost(), temp->getDesc());
        } else {
            return display_minion_no_ability(temp->getName(), temp->getCost(), 
                                                temp->getAttack(), temp->getDefense());
        }
    } else if (auto temp = dynamic_cast<Spell*>(card.get())) {
        return display_spell(temp->getName(), temp->getCost(), temp->getDesc());
    } else if (auto temp = dynamic_cast<Ritual*>(card.get())) {
        return display_ritual(temp->getName(), temp->getCost(), temp->getActivation(), 
                                                        temp->getDesc(), temp->getCharges());
    } else if (auto temp = dynamic_cast<Enchantment*>(card.get())) {
        // checking what type of enchantment it is
        if (temp->getAttack().length() == 0 && temp->getDefense().length() == 0){
            return display_enchantment(temp->getName(), temp->getCost(), temp->getDesc());
        } else {
        return display_enchantment_attack_defence(temp->getName(), temp->getCost(), 
                                temp->getDesc(), temp->getAttack(), temp->getDefense());
        }
    } else {return CARD_TEMPLATE_BORDER;}
}

// helper that takes the board of Cards and creates a vector of card_template_t
std::vector<card_template_t> convertBoardRow(std::vector<std::unique_ptr<Card>>& board, bool hand){
    std::vector<card_template_t> result;
    size_t lower = 1;
    size_t upper = 5; 

    if (hand){
        lower = 0;
        upper = 4;
    } 

    for (size_t i = lower; i <= upper; ++i) {
        if (i < board.size() && board[i]) {
            result.push_back(convertCard(board[i]));
        } else {
            // if there is an empty space on the board
            result.push_back(CARD_TEMPLATE_BORDER);
        }
    }
    return result;
}

// helper that takes the board of Cards, graveyard, and Player info to create a vector of card_template_t
std::vector<card_template_t> convertPlayerRow(std::vector<std::unique_ptr<Card>>& board, 
                                                        std::vector<std::unique_ptr<Card>>& graveyard, 
                                                            int playerNum, std::string name,int life,int mana){
    std::vector<card_template_t> result;

    // checking for ritual
    if (!board.empty() && board[0]){
        result.push_back(convertCard(board[0]));
    } else {result.push_back(CARD_TEMPLATE_BORDER);}

    // empty spots and player info
    result.push_back(CARD_TEMPLATE_EMPTY);
    result.push_back(display_player_card(playerNum, name, life, mana));
    result.push_back(CARD_TEMPLATE_EMPTY);

    // checking for graveyard topdeck
    if (!graveyard.empty() && graveyard.back()) {
        result.push_back(convertCard(graveyard.back()));
    } else { result.push_back(CARD_TEMPLATE_BORDER); }

    return result;
}

// helper that prints horizontal border (0 is upper, 1 is lower)
void printHBorder(int upOrLow){
    if (upOrLow == 0){std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;}
    else{std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;}
    for (size_t row = 0; row < 165; row++) {std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;}
    if (upOrLow == 0){std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;}
    else{std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;}
}

// helper that prints a row of cards with the side border
void printRow(std::vector<card_template_t>& cards){
    for (size_t row = 0; row < cards[0].size(); row++) {
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (const auto& card : cards) {
            std::cout << card[row];
        }
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << '\n';
    }
}

// helper that prints middle of the board
void printLogo(){
    for (const auto& row : CENTRE_GRAPHIC) {
        std::cout << row << std::endl;
    }
}

// prints hand of Cards from Player
void Board::printHand(Player &active){
    auto cards = convertBoardRow(active.getHand(), true);
    for (size_t row = 0; row < cards[0].size(); row++) {
        for (const auto& card : cards) {
            std::cout << card[row];
        }
        std::cout << std::endl;
    }
}

// prints minion and enchantments
void Board::inspectMinion(Player &active, int i){
    auto minion = convertCard(active.getBoard()[i]);
    for (const auto& c : minion) {
        std::cout << c << std::endl;
    }

    std::vector<card_template_t> enchantments;
    auto temp = dynamic_cast<Minion*>(active.getBoard()[i].get());
    for (int i = 0; i < temp->getEnchantmentsSize(); ++i) {
        enchantments.push_back(convertCard(temp->getEnchantments()[i]));
    }

    if (enchantments.empty()) { return; }

    int groupSize = 5;

    for (size_t start = 0; start < enchantments.size(); start += groupSize) {
        size_t end = start + groupSize;
        if (enchantments.size() < end) {end = enchantments.size();}

        // Print each row of the current group
        for (size_t row = 0; row < enchantments[0].size(); ++row) {
            for (size_t i = start; i < end; ++i) {
                std::cout << enchantments[i][row];
            }
            std::cout << std::endl;
        }
    }
}

// prints the entire board; player one is always at the top
void Board::printBoard(Player &p1, Player &p2){
    auto player1 = convertPlayerRow(p1.getBoard(), p1.getGraveyard(), 1, p1.getName(), p1.getLife(), p1.getMagic());
    auto cards1 = convertBoardRow(p1.getBoard(), false);
    auto player2 = convertPlayerRow(p2.getBoard(), p2.getGraveyard(), 2, p2.getName(), p2.getLife(), p2.getMagic());
    auto cards2 = convertBoardRow(p2.getBoard(), false);

    printHBorder(0);
    printRow(player1);
    printRow(cards1);
    printLogo();
    printRow(cards2);
    printRow(player2);
    printHBorder(1);
}


// OBSERVER PATTERN FUNCTIONS

Board::~Board(){}

void Subject::setState(EventType e) {eventState = e;}
EventType Subject::getState() {return eventState;}

void Subject::notifyObservers(Player &active, Player &inactive, int index, bool bothStandstill){
    for (auto& card : active.getBoard()) {
        if (auto* observer = dynamic_cast<Observer*>(card.get())) {
            observer->notify(eventState, active, index, bothStandstill);
        }
    }

    for (auto& card : inactive.getBoard()) {
        if (auto* observer = dynamic_cast<Observer*>(card.get())) {
            observer->notify(eventState, active, index, bothStandstill);
        }
    }
}
