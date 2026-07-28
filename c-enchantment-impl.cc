module enchantment;
import <vector>;
import <string>;
import <iostream>;
import <tuple>;
import plard;
import minion;
import carddata;

using namespace std;

std::string Enchantment::getAttack() {return attack;}
std::string Enchantment::getDefense() {return defense;}
std::string Enchantment::getDesc() {return desc;}

//tuple ctor
Enchantment::Enchantment(string name, vector<tuple<string, int, string, string, string>> vec) : Card{name} {
  int i = 0;
  if (name == "Giant Strength") { i = 0; }
  else if (name == "Enrage") { i = 1; }
  else if (name == "Haste") { i = 2; }
  else if (name == "Magic Fatigue") { i = 3; }
  else if (name == "Silence") { i = 4; }

  tuple<string, int, string, string, string> temp = (vec[i]);
  this->setName(get<0>(temp));
  this->setCost(get<1>(temp));
  this->desc = (get<2>(temp));
  this->attack = (get<3>(temp));
  this->defense = (get<4>(temp));
}

void Enchantment::giantStrength(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->giantStrength(temp);
  } else cerr << "Out of bounds!" << endl;
}

void Enchantment::giantStrength(Minion *temp) {
  temp->addA(2);
  temp->addD(2);
}

void Enchantment::enrage(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->enrage(temp);
  } else cerr << "Out of bounds!" << endl;
}

void Enchantment::enrage(Minion *temp) {
  temp->multA(2);
  temp->multD(2);
}

void Enchantment::haste(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
    Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
    this->haste(temp);
  } else cerr << "Out of bounds!" << endl;
}

void Enchantment::haste(Minion *temp) {
    temp->addAction(1);
}

void Enchantment::magicFatigue(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->magicFatigue(temp);
  } else cerr << "Out of bounds!" << endl;
}

void Enchantment::magicFatigue(Minion *temp) {
  temp->addAbilityCost(2);
}

void Enchantment::silence(Player *played, Player *owner, int p) {
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->silence(temp);
  } else cerr << "Out of bounds!" << endl;
}

void Enchantment::silence(Minion *temp) {
  temp->setHasAbility(false);
}

