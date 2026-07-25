module board;

import plard;
import state;
import ascii_graphics;

import minion;
import ritual;
import enchantment;
import spell;

import <vector>;
import <string>;
import <iostream>;
import <memory>;

card_template_t Board::convertCard(std::unique_ptr<Card>& card){
    if (auto temp = dynamic_cast<Minion*>(card.get())) {
        if (temp->getHasAbility() && (temp->getAbilityCost() < 0)){
            return display_minion_triggered_ability(temp->getName(), temp->getCost(), temp->getAttack(), temp->getDefense(), temp->getDesc());
        } else if (temp->getHasAbility()) {
            return display_minion_activated_ability(temp->getName(), temp->getCost(), temp->getAttack(), temp->getDefense(), temp->getAbilityCost(), temp->getDesc());
        } else {
            return display_minion_no_ability(temp->getName(), temp->getCost(), temp->getAttack(), temp->getDefense());
        }
    } else if (auto temp = dynamic_cast<Spell*>(card.get())) {
        return display_spell(temp->getName(), temp->getCost(), temp->getDesc());
    } else if (auto temp = dynamic_cast<Ritual*>(card.get())) {
        return display_ritual(temp->getName(), temp->getCost(), temp->getActivation(), temp->getDesc(), temp->getCharges());
    } else if (auto temp = dynamic_cast<Enchantment*>(card.get())) {
        if (temp->getAttack().length() == 0 && temp->getDefense().length() == 0){
            return display_enchantment(temp->getName(), temp->getCost(), temp->getDesc());
        }
        return display_enchantment_attack_defence(temp->getName(), temp->getCost(), temp->getDesc(), temp->getAttack(), temp->getDefense());
    } else {return CARD_TEMPLATE_BORDER; }

    // if (std::find(minionCards.begin(), minionCards.end(), card->getName()) != minionCards.end()) { 
    //     Minion *temp = dynamic_cast<Minion*>(card);
    //     if (temp->hasAbility && (temp->abilityCost < 0)){
    //         return display_minion_triggered_ability(temp->name, temp->cost, temp->attack, temp->defence, temp->desc);
    //     } else if (temp->hasAbility) {
    //         return display_minion_activated_ability(temp->name, temp->cost, temp->attack, temp->defence, temp->abilityCost, temp->desc);
    //     } else {
    //         return display_minion_no_ability(temp->name, temp->cost, temp->attack, temp->defence);
    //     }
    // } else if (std::find(spellCards.begin(), spellCards.end(), card->getName()) != spellCards.end()) {
    //     Spell *temp = dynamic_cast<Spell*>(card);
    //     return display_spell(temp->name, temp->cost, temp->desc);
    // } else if (std::find(ritualCards.begin(), ritualCards.end(), card->getName()) != ritualCards.end()) {
    //     Ritual *temp = dynamic_cast<Ritual*>(card);
    //     return display_ritual(temp->name, temp->cost, temp->activataion, temp->ritual_desc, temp->charges);
    // } else if (std::find(enchantmentCards.begin(), enchantmentCards.end(), card->getName()) != enchantmentCards.end()) {
    //     Enchantment *temp = dynamic_cast<Enchantment*>(card);
    //     if (temp->attack == "" && temp->defense == ""){
    //         return display_enchantment(temp->name, temp->cost, temp->desc);
    //     }
    //     return display_enchantment_attack_defence(temp->name, temp->cost, temp->desc, temp->attack, temp->defence);
    // } 
    // return display_minion_no_ability("NOTHING", 0, 0, 0);
}

std::vector<card_template_t> Board::convertBoardRow(std::vector<std::unique_ptr<Card>>& board){
    std::vector<card_template_t> result;
    // result.reserve(board.size());

    for (size_t i = 1; i <= 5; ++i) {
        if (i < board.size() && board[i]) {
            result.push_back(convertCard(board[i]));
        } else {
            result.push_back(CARD_TEMPLATE_BORDER);
        }
    }

    return result;
}

std::vector<card_template_t> Board::convertPlayerRow(std::vector<std::unique_ptr<Card>>& board, std::vector<std::unique_ptr<Card>>& graveyard, int playerNum,
                                                            std::string name,int life,int mana){
    std::vector<card_template_t> result;
    if (board[0]){
        result.push_back(convertCard(board[0]));
    } else {result.push_back(CARD_TEMPLATE_EMPTY);}
    result.push_back(CARD_TEMPLATE_EMPTY);
    result.push_back(display_player_card(playerNum, name, life, mana));
    result.push_back(CARD_TEMPLATE_EMPTY);
    if (!board.empty() && board.back()) {
        result.push_back(convertCard(board.back()));
    } else { result.push_back(CARD_TEMPLATE_EMPTY); }

    return result;
}

void Board::printHBorder(int upOrLow){
    if (upOrLow == 0){std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;}
    else{std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;}
    for (size_t row = 0; row < 165; row++) {
        std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    if (upOrLow == 0){std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;}
    else{std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;}
}

void Board::printRow(std::vector<card_template_t>& cards){
    for (size_t row = 0; row < cards[0].size(); row++) {
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (const auto& card : cards) {
            std::cout << card[row];
        }
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << '\n';
    }
}

void Board::printLogo(){
    for (const auto& row : CENTRE_GRAPHIC) {
        std::cout << row << '\n';
    }
}

void Board::printBoard(Player &p1, Player &p2){
    auto player1 = convertPlayerRow(p1.getBoard(), p1.getGraveyard(), 1, p1.getName(), p1.getLife(), p1.getMagic());
    auto cards1 = convertBoardRow(p1.getBoard());
    auto player2 = convertPlayerRow(p2.getBoard(), p2.getGraveyard(), 2, p2.getName(), p2.getLife(), p2.getMagic());
    auto cards2 = convertBoardRow(p2.getBoard());

    printHBorder(0);
    printRow(player1);
    printRow(cards1);
    printLogo();
    printRow(cards2);
    printRow(player2);
    printHBorder(1);
    
    // card_template_t pcard1 = display_minion_no_ability("pee", 5, 8, 8);
    // card_template_t pcard2 = display_minion_no_ability("pee1", 5, 8, 8);
    // card_template_t pcard3 = display_minion_no_ability("pee2", 5, 8, 8);
    // card_template_t pcard4 = display_minion_no_ability("pee3", 5, 8, 8);
    // card_template_t pcard5 = display_minion_no_ability("pee4", 5, 8, 8);
    // card_template_t p2card1 = display_minion_no_ability("poo", 5, 8, 8);
    // card_template_t p2card2 = display_minion_no_ability("poo1", 5, 8, 8);
    // card_template_t p2card3 = display_minion_no_ability("poo2", 5, 8, 8);
    // card_template_t p2card4 = display_minion_no_ability("poo3", 5, 8, 8);
    // card_template_t p2card5 = display_minion_no_ability("poo4", 5, 8, 8);

    // card_template_t size = CARD_TEMPLATE_BORDER;

    // std::vector<card_template_t> cards = {
    //     pcard1,
    //     pcard2,
    //     pcard3,
    //     pcard4,
    //     pcard5
    // };

    // std::vector<card_template_t> cards2 = {
    //     p2card1,
    //     p2card2,
    //     p2card3,
    //     p2card4,
    //     p2card5
    // };

    // card_template_t p11 = display_ritual("P1 Dark Ritual", 0, 1, "At the start of your turn, gain 1 magic", 5);
    // card_template_t p12 = CARD_TEMPLATE_EMPTY;
    // card_template_t p13 = display_player_card(1, "pee", 0, 0);
    // card_template_t p14 = CARD_TEMPLATE_EMPTY;
    // card_template_t p15 = display_minion_no_ability("Graveyard Minion", 0, 6, 7);

    // card_template_t p21 = display_ritual("P2 Dark Ritual", 0, 1, "At the start of your turn, gain 1 magic", 5);
    // card_template_t p22 = CARD_TEMPLATE_EMPTY;
    // card_template_t p23 = display_player_card(2, "poo", 0, 0);
    // card_template_t p24 = CARD_TEMPLATE_EMPTY;
    // card_template_t p25 = display_minion_no_ability("Graveyard Minion", 0, 6, 7);

    // std::vector<card_template_t> player1 = {
    //     p11,
    //     p12,
    //     p13,
    //     p14,
    //     p15
    // };

    // std::vector<card_template_t> player2 = {
    //     p21,
    //     p22,
    //     p23,
    //     p24,
    //     p25
    // };
}
