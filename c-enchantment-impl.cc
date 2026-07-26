module enchantment;
import <vector>;
import <string>;
import <iostream>;
import plard;
import minion;

using namespace std;

std::string Enchantment::getAttack() {return attack;}
std::string Enchantment::getDefense() {return defense;}
std::string Enchantment::getDesc() {return desc;}

//CTOR
Enchantment::Enchantment(string name, int cost): Card{name, cost} {
    cout << "enchantment ctor" << endl;
    if (name == "Giant Strength") { this->attack = "+2"; this->defense = "+2"; }
    else if (name == "Enrage") { this->attack = "*2"; this->defense = "*2"; }
    else if (name == "Haste") { this->desc = "Enchanted minion gains +1 action each turn"; }
    else if (name == "Magic Fatigue") { this->desc = "Enchanted minion's activated ability costs 2 more"; }
    else if (name == "Silence") { this->desc = "Enchanted minion cannot use abilities"; }
}

//selects which spell to use
// void Ritual::playRitual(Player *played, Player *owner, int *p) {
//     string name = s.getName();
//     if (name == "Giant Strength") { giantStrength(played, owner, p); }
//     else if (name == "Enrage") { enrage(played, owner, p); }
//     else if (name == "Haste") { haste(played, owner, p); }
//     else if (name == "Magic Fatigue") { magicFatigue(played, owner, p); }
//     else if (name == "Silence") { silence(played, owner, p); }
// }

void Enchantment::giantStrength(Player *played, Player *owner, int p) {
  cout << "giantStrength called" << endl;
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->giantStrength(temp);
  } else cout << "bad index" << endl;
}

void Enchantment::giantStrength(Minion *temp) {
  temp->addA(2);
  temp->addD(2);
}

void Enchantment::enrage(Player *played, Player *owner, int p) {
  cout << "enrage called" << endl;
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->enrage(temp);
  } else cout << "bad index" << endl;
}

void Enchantment::enrage(Minion *temp) {
  temp->multA(2);
  temp->multD(2);
}

void Enchantment::haste(Player *played, Player *owner, int p) {
  cout << "haste called" << endl;
  if ((owner) && (owner->getSizeB() > p)) {
    Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
    this->haste(temp);
  } else cout << "bad index" << endl;
}

void Enchantment::haste(Minion *temp) {
    temp->addAction(1);
}

void Enchantment::magicFatigue(Player *played, Player *owner, int p) {
  cout << "magicFatigue called" << endl;
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->magicFatigue(temp);
  } else cout << "bad index" << endl;
}

void Enchantment::magicFatigue(Minion *temp) {
  temp->addAbilityCost(2);
}

void Enchantment::silence(Player *played, Player *owner, int p) {
  cout << "silence called" << endl;
  if ((owner) && (owner->getSizeB() > p)) {
  Minion *temp = dynamic_cast<Minion*>(owner->getCardB(p));
  this->silence(temp);
  } else cout << "bad index" << endl;
}

void Enchantment::silence(Minion *temp) {
  temp->setHasAbility(false);
}


// |-------------------------------||-------------------------------||-------------------------------|
// | Giant Strength          |   1 || Enrage                  |   2 || Haste                   |   1 |
// |-------------------------------||-------------------------------||-------------------------------|
// |                   Enchantment ||                   Enchantment ||                   Enchantment |
// |-------------------------------||-------------------------------||-------------------------------|
// |                               ||                               || Enchanted minion gains +1     |
// |                               ||                               || action each turn              |
// |                               ||                               ||                               |
// |------                   ------||------                   ------||                               |
// | +2  |                   |  +2 || *2  |                   |  *2 ||                               |
// |-------------------------------||-------------------------------||-------------------------------|
// |-------------------------------||-------------------------------|
// | Magic Fatigue           |   0 || Silence                 |   1 |
// |-------------------------------||-------------------------------|
// |                   Enchantment ||                   Enchantment |
// |-------------------------------||-------------------------------|
// | Enchanted minion's activated  || Enchanted minion cannot use   |
// | ability costs 2 more          || abilities                     |
// |                               ||                               |
// |                               ||                               |
// |                               ||                               |
// |-------------------------------||-------------------------------|
