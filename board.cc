export module board;

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

export class Board{
  // Player* p1, p2;

 public:
  // will convert all cards into card_template_t so they can be printed properly
  card_template_t convertCard(std::unique_ptr<Card>& card);
  std::vector<card_template_t> convertBoardRow(std::vector<std::unique_ptr<Card>>& board, bool hand);
  std::vector<card_template_t> convertPlayerRow(std::vector<std::unique_ptr<Card>>& board, 
        std::vector<std::unique_ptr<Card>>& graveyard, int playerNum, std::string name,int life,int mana);
  // 0 is upper border, 1 is lower border
  void printHBorder(int upOrLow);
  void printRow(std::vector<card_template_t>& cards);
  void printLogo();
  void printBoard(Player &p1, Player &p2);
  void printHand(Player &active);
  void inspectMinion(Player &active, int i);
  // void printCard(card_template_t card);
  // notifyWhenTriggered();
};

// Board b{};
// b.printBoard();

