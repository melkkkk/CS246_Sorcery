export module board;

import plard;
import ascii_graphics;

import <vector>;
import <string>;
import <iostream>;

export class Board{
  Player* p1, p2;
  // MAY CHANGE LOCATION LATER
  inline static std::vector<std::string> spellCards = {"Banish", "Unsummon", "Recharge", "Disenchant", "Raise Dead", "Blizzard"};
  inline static std::vector<std::string> ritualCards = {"Dark Ritual", "Aura of Power", "Standstill"};
  inline static std::vector<std::string> minionCards = {"Air Elemental", "Earth Elemental", "Bone Golem", "Potion Seller", 
                                                          "Novice Pyromancer", "Apprentice Summoner", "Fire Elemental", "Master Summoner"};
  inline static std::vector<std::string> enchantmentCards = {"Giant Strength", "Enrage", "Haste", "Magic Fatigue", "Silence"};

 public:
  // will convert all cards into card_template_t so they can be printed properly
  card_template_t convertCard();
  std::vector<card_template_t> convertBoardRow();
  std::vector<card_template_t> convertPlayerRow();
  // 0 is upper border, 1 is lower border
  void printHBorder(int upOrLow);
  void printRow(std::vector<card_template_t>& cards);
  void printLogo();
  void printBoard();
  void printHand(Player *active);
  // void printCard(card_template_t card);
  // notifyWhenTriggered();
};

// Board b{};
// b.printBoard();

