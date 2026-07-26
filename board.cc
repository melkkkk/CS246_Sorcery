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
  
 public:
  void printBoard(Player &p1, Player &p2);
  void printHand(Player &active);
  void inspectMinion(Player &active, int i);

  // notifyWhenTriggered();
};

export class Subject{
  
  virtual ~Subject() = 0;
}
//void Subject::attach(Observer *o) { observers.emplace_back(o); }
//void Subject::notifyObservers() { for (auto &ob : observers) ob->notify(*this); }
//void Subject::setState(State newS) { state = newS; }
//State Subject::getState() const { return state; }

