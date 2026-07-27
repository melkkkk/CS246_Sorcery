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


export class Subject{
  EventType eventState;
 public:
  void notifyObservers(Player &active, Player &inactive, int index, bool bothStandstill);
  void setState(EventType e);
  EventType getState();
  virtual ~Subject() = default;
};

export class Board: public Subject{
 public:
  void printBoard(Player &p1, Player &p2);
  void printHand(Player &active);
  void inspectMinion(Player &active, int i);
  ~Board();
};

