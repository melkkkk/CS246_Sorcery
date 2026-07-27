module spell;
import <vector>;
import <string>;
import <iostream>;
import state;
import plard;
import minion;
import ritual;

using namespace std;

std::string Spell::getDesc(){return desc;}

//CTOR
Spell::Spell(string name, int cost): Card{name, cost} {
    cout << "spell ctor" << endl;
    if (name == "Banish") { this->desc = "Destroy target minion or ritual"; }
    else if (name == "Unsummon") { this->desc = "Return target minion to its owner's hand"; }
    else if (name == "Recharge") { this->desc = "Your ritual gains 3 charges"; }
    else if (name == "Disenchant") { this->desc = "Destroy the top enchantment"; }
    else if (name == "Raise Dead") { this->desc = "Resurrect the top minion in your graveyard and set its defence to 1"; }
    else if (name == "Blizzard") { this->desc = "Deal 2 damage to all minions"; }
}

//selects which spell to use
// void Spell::playspell(Player *played, Player *owner, Spell s, int *p) {
//     string name = s.getName();
//     if (name == "Banish") { banish(played, owner, p); }
//     else if (name == "Unsummon") { unsummon(played, owner, p); }
//     else if (name == "Recharge") { recharge(played); }
//     else if (name == "Disenchant") { disenchant(played, owner, p); }
//     else if (name == "Raise Dead") { raiseDead(played); }
//     else if (name == "Blizzard") { blizzard(played, owner); }
// }

void Spell::banish(Player *played, int indexC, Player *owner, int i) {
  cout << "banish called" << endl;
  if ((owner) && (owner->getSizeB() > i)) {
    //owner->removeFromBoard(i);
    if (i != 0) owner->removeFrom(owner->getBoard(), i);
    else owner->getUniqueB(0) = nullptr;
  } else cout << "bad index" << endl;
}

void Spell::unsummon(Player *played, int indexC, Player *owner, int i) {
  cout << "unsummon called" << endl;
  // check not null, i is in board, hand not already full
  if ((owner) && (owner->getSizeB() > i) && (owner->getSizeH() < 5) && (i != 0)) {
    owner->moveToFrom(owner->getHand(), owner->getBoard(), move(owner->getUniqueB(i)), i);
  } else cout << "bad index" << endl;
}

void Spell::recharge(Player *played, int indexC) {
  cout << "recharge called" << endl;
  if ((played->getSizeB() > 0) && (played->getCardB(0))) {
    Ritual *temp = dynamic_cast<Ritual*>(played->getCardB(0));
    if (temp) temp->addC(3);
    else cout << "null temp" << endl;
  } else cout << "bad index" << endl;
}

//
void Spell::disenchant(Player *played, int indexC, Player *owner, int i) {
  cout << "disenchant called" << endl;
  if ((owner) && (owner->getSizeB() > i)) {
    Minion *temp = dynamic_cast<Minion*>(owner->getCardB(i));
    int in = temp->getSizeE() - 1; //remove most recently added value
    temp->removeE(in);
  } else cout << "bad index" << endl;
}

void Spell::raiseDead(Player *played, int indexC) {
  cout << "raise dead called" << endl;
  //check not null, i is in board, hand not already full
  if ((played->getSizeB() < 5) && (played->getSize(played->getGraveyard()) > 0)){
    played->moveToFrom(played->getBoard(), played->getGraveyard(), move(played->getUnique(played->getGraveyard(), 0)), 0);
  } else cout << "bad index" << endl;
}

void Spell::blizzard(Player *played, int indexC, Player *owner){
  cout << "blizzard called" << endl;
  if (owner) {
    int len = owner->getSizeB();
    for (int i = 1; i < len; i++) {
      Minion *temp = dynamic_cast<Minion*>(owner->getCardB(i));
      temp->addD(-2);
    }
  } else cout << "bad index" << endl;
}


// |-------------------------------||-------------------------------||-------------------------------|
// | Banish                  |   2 || Unsummon                |   1 || Recharge                |   1 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy target minion or      || Return target minion to its   || Your ritual gains 3 charges   |
// | ritual                        || owner's hand                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------||-------------------------------|
// | Disenchant              |   1 || Raise Dead              |   1 || Blizzard                |   3 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                         Spell ||                         Spell ||                         Spell |
// |-------------------------------||-------------------------------||-------------------------------|
// | Destroy the top enchantment   || Resurrect the top minion in   || Deal 2 damage to all minions  |
// | on target minion              || your graveyard and set its.   ||                               |
// |                               || defence to 1                  ||                               |
// |                               ||                               ||                               |
// |                               ||                               ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
