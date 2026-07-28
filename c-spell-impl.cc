module spell;
import <vector>;
import <string>;
import <tuple>;
import <iostream>;
import state;
import plard;
import minion;
import ritual;
import carddata;

using namespace std;

std::string Spell::getDesc(){return desc;}

//tuple ctor
Spell::Spell(string name, vector<tuple<string, int, string>> vec) : Card{name} {
  int i = 0;
  if (name == "Banish") { i = 0; }
  else if (name == "Unsummon") { i = 1; }
  else if (name == "Recharge") { i = 2; }
  else if (name == "Disenchant") { i = 3; }
  else if (name == "Raise Dead") { i = 4; }
  else if (name == "Blizzard") { i = 5; }

  tuple<string, int, string> temp = (vec[i]);
  this->setName(get<0>(temp));
  this->setCost(get<1>(temp));
  this->desc = (get<2>(temp));
}

void Spell::banish(Player *played, int indexC, Player *owner, int i) {
  if ((owner) && (owner->getSizeB() > i)) {
    if (i != 0) {
      Minion *temp = dynamic_cast<Minion*>(owner->getCardB(i));
      temp->clearEffects();

      owner->removeFrom(owner->getBoard(), i);
    }
    else owner->getUniqueB(0) = nullptr;
  } else cerr << "Out of bounds!" << endl;
}

void Spell::unsummon(Player *played, int indexC, Player *owner, int i) {
  // check not null, i is in board, hand not already full
  if ((owner) && (owner->getSizeB() > i) && (owner->getSizeH() < 5) && (i != 0)) {
    Minion *temp = dynamic_cast<Minion*>(owner->getCardB(i));
    temp->clearEffects();
      
    owner->moveToFrom(owner->getHand(), owner->getBoard(), move(owner->getUniqueB(i)), i);
  } else cerr << "Out of bounds!" << endl;
}

void Spell::recharge(Player *played, int indexC) {
  if ((played->getSizeB() > 0) && (played->getCardB(0))) {
    Ritual *temp = dynamic_cast<Ritual*>(played->getCardB(0));
    if (temp) temp->addC(3);
    else cerr << "No ritual to call this on!" << endl;
  } else cerr << "Out of bounds!" << endl;
}

//
void Spell::disenchant(Player *played, int indexC, Player *owner, int i) {
  if ((owner) && (owner->getSizeB() > i)) {
    Minion *temp = dynamic_cast<Minion*>(owner->getCardB(i));
    int in = temp->getSizeE() - 1; //remove most recently added value
    temp->removeE(in);

    //loop the strings and remove most recent enchantment
    int len = temp->getSizeA() - 1;
    string current = "";
    for (int j = len; j >= 0; j--) {
      current = temp->getAllApplied()[j];
      if (current == "Giant Strength" || current == "Enrage" || current == "Haste" || current == "Magic Fatigue" || current == "Silence") {
        temp->removeA(j);
        return;
      }
    }

  } else cerr << "Out of bounds!" << endl;
}

void Spell::raiseDead(Player *played, int indexC) {
  //check not null, i is in board, hand not already full
  if ((played->getSizeB() < 5) && (played->getSize(played->getGraveyard()) > 0)){
    int index = played->getSize(played->getGraveyard()) - 1; //get newest dead value
    Minion *temp = dynamic_cast<Minion*>(played->getCardG(index));
    temp->setDefense(1);
    temp->addApply("Raise Dead");
    played->moveToFrom(played->getBoard(), played->getGraveyard(), move(played->getUnique(played->getGraveyard(), index)), index);
  } else cerr << "Out of bounds!" << endl;
}

void Spell::blizzard(Player *played, Player *owner){
  if (owner) {
    int len = owner->getSizeB();
    for (int i = 1; i < len; i++) {
      Minion *temp = dynamic_cast<Minion*>(owner->getCardB(i));
      temp->addD(-2);
      temp->addApply("Blizzard");
    }
    len = played->getSizeB();
    for (int i = 1; i < len; i++) {
      Minion *temp = dynamic_cast<Minion*>(played->getCardB(i));
      temp->addD(-2);
      temp->addApply("Blizzard");
    }
  } else cerr << "Out of bounds!" << endl;
}
